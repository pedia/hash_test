#include <boost/lexical_cast.hpp>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <cstdlib> // for random
#include <map>
#include <vector>
// #include <set>

#include "ptime.h"
#include "allhash.h"

typedef uint32_t (*Hash32)(const char *, size_t);
typedef uint64_t (*Hash64)(const char *, size_t);

template<typename InputIterator, typename HashFunction, typename ResultType>
void Test(const char *name, InputIterator b, InputIterator e, HashFunction f
	, ResultType& dummy, size_t BlobSize) {
	InputIterator a = b;
	ptime pt;
	// 1
	volatile uint32_t k; // avoid loop optimize
	while (b != e) {
		k = f((const char *)&(*b++), sizeof(dummy));
	}
	double time_used = pt.wall_clock();
	b = a;

	// 2
	typedef std::map<ResultType, int> ResultMap;
	ResultMap map2;
	while (b != e) {
		ResultType t = f((const char *)&(*b++), BlobSize);
		++ map2[t];
	}

	// check
	int collided_count = 0;
	for (typename ResultMap::const_iterator i=map2.begin(); i!=map2.end(); ++i) {
			if (i->second > 1) {
				collided_count += i->second;
			}
	}

	std::cout 
		<< std::left  << std::setw(16) << name 
		<< std::right << std::setw(8) << std::setprecision(4) << time_used 
		<< std::right << std::setw(15) << map2.size()
		<< std::right << std::setw(15) << collided_count
		<< std::endl;
}

std::string CreateRandomString(size_t length) {
	std::string s(length, ' ');
	for (size_t i=0; i<length; ++i)
		// s[i] = 'A' + rand() % ('z'-'A');
		s[i] = '!' + rand() % ('~'-'!');
	return s;
}

#if 0
template<typename HashFunction>
void TestHashNumber(const char* name, HashFunction func) {
	// 1
  const int FROM = 0;
  const int COUNT = 10000;

  volatile uint32 k; // avoid optimize
  ptime pt(name, false);
  for (uint32 i=FROM; i<FROM + COUNT; ++i) {
    k = func((char*)&i, sizeof(uint32));
  }
  double time_used = pt.wall_clock();

  // 2
  // run 1 billion result:
  // crc32	1.945	0	0
  // crc-O	0.199	0	0
  // md5	1.969	1156173	2303355
  // doobs	0.205	1153288	2297689

  const int COLLIDE_COUNT = 1000000;
  std::map<uint32, int> map2;
  for (uint32 i=FROM; i<FROM + COLLIDE_COUNT; ++i) {
    uint32 h = func((char*)&i, sizeof(uint32));
    ++ map2[h];
  }

  // check
  int collided_count = 0;
  for (std::map<uint32, int>::const_iterator i=map2.begin();
    i!=map2.end(); ++i) {
    if (i->second > 1)
      collided_count += i->second;
  }

  // 3
  std::cout << name << "\t" << time_used 
	    << "\t" << COLLIDE_COUNT-map2.size()
	    << "\t" << collided_count
	    << std::endl;
}

// integer in "%d" style
template<typename HashFunction>
void TestHashNumberString(const char* name, HashFunction func) {
  const int FROM = 200000;
  const int COUNT = 10000;

  ptime pt(name, false);
  for (int i=FROM; i<FROM + COUNT; ++i) {
    std::string t2 = boost::lexical_cast<std::string>(i);
    func(t2.c_str(), t2.size());
  }
  double time_used = pt.wall_clock();

  // 2
  const int COLLIDE_COUNT = 1000000;
  std::map<uint32, int> map2;
  for (int i=FROM; i<FROM + COLLIDE_COUNT; ++i) {
    std::string t = boost::lexical_cast<std::string>(i);
    uint32 h = func(t.c_str(), t.size());
    ++ map2[h];
  }

  // 条目数
  int collided_count = 0;
  for (std::map<uint32, int>::const_iterator i=map2.begin();
    i!=map2.end(); ++i) {
      if (i->second > 1)
        collided_count += i->second;
  }

  // 3
  std::cout << name << "\t" << time_used 
    << "\t" << COLLIDE_COUNT-map2.size()
    << "\t" << collided_count
    << std::endl;
}

static std::vector<std::string> samples(1000000);
static bool once = false;

// random string
template<typename HashFunction>
void TestHashRandomString(const char* name, HashFunction func) {
  // 1 随机字符串
  // 2 0-50w 的冲突百分比，分布均匀性

  const int COUNT = 10000;
  const int COLLIDE_COUNT = 1000000;
  
  if (!once) {
    srand(123123);
    once = true;
    std::set<std::string> uniq;
    for (size_t i=0; i<samples.size(); ++i) {
      samples[i] = CreateRandomString(5 + rand() % 60);
      uniq.insert(samples[i]);
    }
    EXPECT_EQ(uniq.size(), samples.size());
  }

  volatile uint32 k; // optimize forbidden
  ptime pt(name, false);
  for (int i=0; i<COUNT; ++i) {
    const std::string& t = samples[i];
    k = func(t.c_str(), t.size());
  }
  double time_used = pt.wall_clock();

  // 2
  std::map<uint32, int> map2;
  for (size_t i=0; i<samples.size(); ++i) {
    const std::string& t = samples[i];
    uint32 h = func(t.c_str(), t.size());
    ++ map2[h];
  }

  // 条目数
  int collided_count = 0;
  for (std::map<uint32, int>::const_iterator i=map2.begin();
    i!=map2.end(); ++i) {
      if (i->second > 1)
        collided_count += i->second;
  }

  // 3
  std::cout << name << "\t" << time_used 
    << "\t" << COLLIDE_COUNT-map2.size()
    << "\t" << collided_count
    << std::endl;
}

TEST(hash, h) {
  std::cout << "\t speed \t collided-item \t collided count\n";
#if 0
  std::cout << "--- mem of number ---\n";
  TestHashNumber("crc32", crc32());
  TestHashNumber("crc-O", crc32_optima());
  TestHashNumber("md5", md5());
  TestHashNumber("doobs", doobs());
  TestHashNumber("murmur", murmur());
  TestHashNumber("stdhash", stdhash());

  std::cout << "--- number to string ---\n";
  TestHashNumberString("crc32", crc32());
  TestHashNumberString("crc-O", crc32_optima());
  TestHashNumberString("md5", md5());
  TestHashNumberString("doobs", doobs());
  TestHashNumberString("murmur", murmur());
  TestHashNumberString("stdhash", stdhash());

  std::cout << "--- random string ---\n";
  TestHashRandomString("crc32", crc32());
  TestHashRandomString("crc-O", crc32_optima());
  TestHashRandomString("md5", md5());
  TestHashRandomString("doobs", doobs());
  TestHashRandomString("murmur", murmur());
  TestHashRandomString("stdhash", stdhash());
 
  std::cout << "--- real uid ---\n";
  TestHashReal("crc32", crc32());
  TestHashReal("crc-O", crc32_optima());
  TestHashReal("md5", md5());
  TestHashReal("doobs", doobs());
  TestHashReal("murmur", murmur());
  TestHashReal("stdhash", stdhash());
#endif

  std::cout << "--- composite key ---\n";
  TestHashComposite("crc32", crc32());
  TestHashComposite("crc-O", crc32_optima());
  TestHashComposite("md5", md5());
  TestHashComposite("doobs", doobs());
  TestHashComposite("murmur", murmur());
  TestHashComposite("stdhash", stdhash());
}
#endif

template<typename ContainerType>
void Run(ContainerType & v, const int BlobSize) {
	uint32_t dummy32;

	struct {
		const char *name;
		Hash32 f;
	} arr_32[] = {
		{"doobs32", &doobs},
		{"crc32", &crc32},
		{"crc32_optima", &crc32_optima},
		{"stdhash_32", &stdhash_32},
		{"boost_hash", &boost_hash},

		{"murmur1_32", &murmur1_32},
		{"murmur1a_32", &murmur1a_32},
		{"murmur2_32", &murmur2_32},
		{"murmur2a_32", &murmur2a_32},
		{"murmur2na_32", &murmur2na_32},
		{"murmur3_32", &murmur3_32},
	};

	for (int i=0; i<sizeof(arr_32) / sizeof(arr_32[0]); ++i)
		Test(arr_32[i].name, v.begin(), v.end(), arr_32[i].f, dummy32, BlobSize);

	uint64_t dummy64;

	struct {
		const char *name;
		Hash64 f;
	} arr_64[] = {
		{"murmur2a_64", &murmur2a_64},
		{"murmur2b_64", &murmur2b_64},
		{"city_64", &city_64},
		{"stdhash_64", &stdhash_64},
	};

	for (int i=0; i<sizeof(arr_64) / sizeof(arr_64[0]); ++i)
		Test(arr_64[i].name, v.begin(), v.end(), arr_64[i].f, dummy64, BlobSize);
}

int main(int argc, char* argv[]) {
	int count = 10000;

	if (argc > 1) {
		count = atoi(argv[1]);
	}

	std::cout 
		<< std::left  << std::setw(16) << "  name"
		<< std::right << std::setw(8) << "time used"
		<< std::right << std::setw(15) << "unique"
		<< std::right << std::setw(15) << "collided\n"
		<< "-----------------------------------------------\n";

	{
		std::vector<uint32_t> v(count);
		for (uint32_t i=0; i<count; ++i)
			v[i] = i;
		Run(v, 4);
	}

	std::cout << "\n";

	{
		std::vector<std::string> v(count);
		for (uint32_t i=0; i<count; ++i)
			v[i] = CreateRandomString(10);

		std::map<std::string, int> map2;
		for (std::vector<std::string>::const_iterator i=v.begin(); i!=v.end(); ++i)
			++ map2[*i];

		int collided_count = 0;
		for (std::map<std::string, int>::const_iterator i=map2.begin(); i!=map2.end(); ++i) {
			if (i->second > 1) {
				collided_count += i->second;
			}
		}
		assert(collided_count == 0);
		assert(map2.size() == v.size());
		map2.clear();

		Run(v, 10);
	}
	
  return 0;
}




