<pre>
Source style: int32, convert to char *
  name          time used         unique      collided
----------------------------------------------------
doobs32            24.97         999890            220
crc32              107.7        1000000              0
crc32_optima       12.64        1000000              0
stdhash_32         7.415           7665         999990
boost_hash         102.3         261249         983303
murmur1_32         14.18        1000000              0
murmur1a_32        14.18        1000000              0
murmur2_32         15.36        1000000              0
murmur2a_32        17.15        1000000              0
murmur2na_32       14.55        1000000              0
murmur3_32          17.6        1000000              0
murmur2a_64        28.16        1000000              0
murmur2b_64        19.17        1000000              0
city_64            18.68        1000000              0
stdhash_64         63.64           7665         999990

Source style: %d format string
  name          time used         unique      collided
----------------------------------------------------
doobs32            24.28         999867            266
crc32              106.1        1000000              0
crc32_optima       12.58        1000000              0
stdhash_32         7.415         861369         277262
boost_hash         101.1         999885            230
murmur1_32         15.39         999931            138
murmur1a_32        14.09         999931            138
murmur2_32         13.66         999519            962
murmur2a_32        17.15         999881            238
murmur2na_32       14.61         999519            962
murmur3_32         17.53         999876            248
murmur2a_64        28.19        1000000              0
murmur2b_64        19.17        1000000              0
city_64            19.03        1000000              0
stdhash_64         64.22         861369         277262

Source style: u:%d format string, length is 12
  name          time used         unique      collided
----------------------------------------------------
doobs32            24.45         999868            264
crc32              106.1        1000000              0
crc32_optima       12.75        1000000              0
stdhash_32         7.415          33138         997864
boost_hash         101.5         991678          16577
murmur1_32          15.3         999872            256
murmur1a_32        14.21         999872            256
murmur2_32         13.71         999898            204
murmur2a_32        17.15         999886            228
murmur2na_32       14.66         999898            204
murmur3_32         17.49         999879            242
murmur2a_64           28        1000000              0
murmur2b_64        19.38        1000000              0
city_64            19.08        1000000              0
stdhash_64         63.99          33138         997864

Source style: random string length is 10
  name          time used         unique      collided
----------------------------------------------------
doobs32            24.99         999867            266
crc32                108        1000000              0
crc32_optima       12.84        1000000              0
stdhash_32         7.413         861369         277262
boost_hash         100.6         999885            230
murmur1_32         14.63         999931            138
murmur1a_32        14.19         999931            138
murmur2_32         15.36         999519            962
murmur2a_32        17.15         999881            238
murmur2na_32       14.56         999519            962
murmur3_32         17.51         999876            248
murmur2a_64        28.08        1000000              0
murmur2b_64           19        1000000              0
city_64            18.61        1000000              0
stdhash_64         64.32         861369         277262
</pre>
