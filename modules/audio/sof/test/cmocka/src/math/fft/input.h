/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 */

/* Input samples for FFT cmocka test */

/* sine wave samples, freq = 1000Hz */
int input_samples[FFT_SIZE_MAX] = {
0,
279466742,
554180337,
819468480,
1070819172,
1303957463,
1514918156,
1700113250,
1856392962,
1981099300,
2072111269,
2127880946,
2147459804,
2130514848,
2077334276,
1988822580,
1866485157,
1712402714,
1529195871,
1319980594,
1088315199,
838139832,
573709453,
299521473,
20239257,
-259387187,
-534601995,
-800724338,
-1053228029,
-1287818508,
-1500505878,
-1687672772,
-1846135871,
-1973200047,
-2066704205,
-2125058033,
-2147269054,
-2132959506,
-2082372763,
-1996369201,
-1876411561,
-1724540073,
-1543337753,
-1335886476,
-1105714555,
-856736735,
-593187609,
-319549599,
-40476716,
239284591,
514976167,
781909071,
1035543332,
1271565160,
1485960316,
1675082385,
1835714795,
1965125524,
2061113564,
2122046360,
2146887571,
2135214701,
2087226281,
2003738493,
1886171291,
1736524248,
1557342547,
1351673697,
1123015695,
875257538,
612613075,
339549341,
60710580,
-219160741,
-495304595,
-763024350,
-1017766652,
-1255198866,
-1471282763,
-1662343208,
-1825130661,
-1956876446,
-2055339843,
-2118846195,
-2146315390,
-2137280235,
-2091894399,
-2010929801,
-1895763480,
-1748354174,
-1571209009,
-1367340855,
-1140217083,
-893700596,
-631984125,
-359518922,
-80939051,
199017424,
475589028,
744071854,
999899569,
1238721077,
1456474522,
1649456372,
1814384408,
1948453548,
2049383555,
2115457821,
2145552560,
2139155923,
2096376704,
2017942488,
1905187277,
1760028802,
1584935907,
1382886557,
1157317190,
912064270,
651299038,
379456568,
101160333,
-178856429,
-455831216,
-725053264,
-981943668,
-1222133257,
-1441536908,
-1636423021,
-1803476991,
-1939857576,
-2043245229,
-2111881541,
-2144599150,
-2140841599,
-2100672796,
-2024775928,
-1914441843,
-1771547094,
-1598522022,
-1398309424,
-1174314497,
-930346929,
-670556100,
-399360509,
-121372629,
158679547,
436032915,
705970271,
963900546,
1205436881,
1426471249,
1623244314,
1792409378,
1931089296,
2036925410,
2108117670,
2143455244,
2142337113,
2104782294,
2031429517,
1923526358,
1782908027,
1611966148,
1413608084,
1191207495,
948546950,
689753598,
419228976,
141574144,
-138488570,
-416195882,
-686824570,
-945771804,
-1188633431,
-1411278882,
-1609921421,
-1781182553,
-1922149484,
-2030424660,
-2104166545,
-2142120944,
-2143642332,
-2108704833,
-2037902662,
-1932440015,
-1794110592,
-1625267088,
-1428781180,
-1207994683,
-966662715,
-708889829,
-439060206,
-161763083,
118285292,
396321881,
667617861,
927559053,
1171724400,
1395961157,
1596455526,
1769797514,
1913038936,
2023743555,
2100028515,
2140596369,
2144757141,
2112440065,
2044194789,
1941182020,
1805153793,
1638423664,
1443827363,
1224674570,
984692615,
727963092,
458852435,
181937654,
-98071507,
-376412676,
-648351850,
-909263911,
-1154711289,
-1380519435,
-1582847824,
-1758255271,
-1903758462,
-2016882690,
-2095703949,
-2138881653,
-2145681439,
-2115987658,
-2050305338,
-1949751599,
-1816036651,
-1651434705,
-1458745297,
-1241245674,
-1002635050,
-746971693,
-478603906,
-202096064,
77849011,
356470036,
629028249,
890888003,
1137595610,
1364955087,
1569099524,
1746556849,
1894308884,
2009842674,
2091193230,
2136976950,
2146415146,
2119347297,
2056233768,
1958147990,
1826758197,
1664299056,
1473533657,
1257706524,
1020488424,
765913944,
498312865,
222236523,
-57619599,
-336495732,
-609648774,
-872432962,
-1120378883,
-1349269496,
-1555211848,
-1734703288,
-1884691043,
-2002624132,
-2086496759,
-2134882427,
-2146958196,
-2122518682,
-2061979551,
-1966370446,
-1837317480,
-1677015574,
-1488191129,
-1274055656,
-1038251153,
-784788162,
-517977561,
-242357241,
37385070,
316491539,
590215147,
853900426,
1103062638,
1333464055,
1541186029,
1722695641,
1874905792,
1995227705,
2081614954,
2132598273,
2147310541,
2125501534,
2067542177,
1974418238,
1847713562,
1689583130,
1502716412,
1290291620,
1055921658,
803592671,
537596247,
262456432,
-17147220,
-296459233,
-570729093,
-835292041,
-1085648413,
-1317540168,
-1527023313,
-1710534974,
-1864954002,
-1987654050,
-2076548247,
-2130124688,
-2147472149,
-2128295586,
-2072921152,
-1982290651,
-1857945519,
-1702000608,
-1517108214,
-1306412973,
-1073498371,
-822325799,
-557167181,
-282532310,
-3092153,
276400594,
551192344,
816609461,
1068137753,
1301499250,
1512724957,
1698222367,
1854836556,
1979903841,
2071297090,
2127461894,
2147443006,
2130900591,
2078115998,
1989986986,
1868012443,
1714266904,
1531365258,
1322418282,
1090979729,
840985884,
576688624,
302583092,
23331252,
-256317403,
-531606634,
-797854345,
-1050532216,
-1285342725,
-1498292233,
-1685758915,
-1844554352,
-1971977765,
-2065861948,
-2124610126,
-2147223115,
-2133316316,
-2083126254,
-1997506558,
-1877913439,
-1726380929,
-1545486278,
-1338306127,
-1108364180,
-859571268,
-596158842,
-322606996,
-43568278,
236211445,
511973705,
779028359,
1032833364,
1269072028,
1483726422,
1673145724,
1834108304,
1963876527,
2060243304,
2121569638,
2146812495,
2135542548,
2087951475,
2004848700,
1887647629,
1738341607,
1559470018,
1354075096,
1125650179,
878080300,
615576105,
342602245,
63801434,
-216084505,
-492295298,
-760133175,
-1015042770,
-1252688605,
-1469028818,
-1660383914,
-1823499341,
-1955600846,
-2054441657,
-2118340700,
-2146211183,
-2137579089,
-2092591232,
-2012012760,
-1897214146,
-1750147875,
-1573315237,
-1369723788,
-1142836192,
-896511335,
-634938690,
-362567062,
-84028923,
195938372,
472573164,
741170471,
997162015,
1236193911,
1454200726,
1647474619,
1812728403,
1947151456,
2048457523,
2114923598,
2145419232,
2139425758,
2097045112,
2018998101,
1906612142,
1761798685,
1587020705,
1385250813,
1159920691,
914862738,
654244876,
382499673,
104248948,
-175774834,
-452809052,
-722141933,
-979192685,
-1219589411,
-1439243464,
-1634418986,
-1801796449,
-1938529110,
-2042291433,
-2111318637,
-2144436713,
-2141082391,
-2101312721,
-2025804103,
-1915840781,
-1773293002,
-1600585205,
-1400654792,
-1176902160,
-933132876,
-673492948,
-402398309,
-124459714,
155595682,
433004720,
703049250,
961136378,
1202876580,
1424158359,
1621218174,
1790704448,
1929734573,
2035943935,
2107526136,
2143263712,
2142548840,
2105393679,
2032430162,
1924899245,
1784629804,
1614007532,
1415934356,
1193779089,
951320129,
692681197,
422261201,
144659423,
-135402710,
-413161925,
-683894118,
-942994697,
-1186056903,
-1408946753,
-1607873357,
-1779453387,
-1920768625,
-2029415593,
-2103546433,
-2141900334,
-2143824976,
-2109287624,
-2038875688,
-1933786727,
-1795808086,
-1627286493,
-1431088150,
-1210549980,
-969422880,
-711807917,
-442086586,
-164846284,
115197710,
393282431,
664678238,
924769254,
1169131873,
1393609996,
1594385719,
1768044264,
1911632063,
2022706986,
2099379881,
2140346700,
2144910685,
2112994210,
2045140110,
1942502440,
1806826853,
1640420909,
1446114825,
1227213343,
987439521,
730871411,
461872702,
185018501,
-94982478,
-373368004,
-645403318,
-906461668,
-1152102994,
-1378149450,
-1580756458,
-1756478094,
-1902325699,
-2015818711,
-2095026849,
-2138602948,
-2145805870,
-2116513108,
-2051222870,
-1951045608,
-1817685128,
-1653409614,
-1461013049,
-1243767698,
-1005368452,
-749869984,
-481617792,
-205174285,
74758809,
353420411,
626071070,
888073564,
1134971779,
1362566490,
1566986785,
1744755903,
1892850360,
2008751379,
2090487725,
2136669233,
2146510453,
2119844004,
2057123429,
1959415473,
1828381946,
1666251453,
1475781497,
1260211574,
1023208080,
768801950,
501320102,
225311843,
-54528500,
-333441426,
-606683210,
-869606577,
-1117739748,
-1346862498,
-1553077924,
-1732878733,
-1883206887,
-2001505618,
-2085762912,
-2134545727,
-2147024370,
-2122986604,
-2062841263,
-1967611292,
-1838916356,
-1678945286,
-1490418857,
-1276543511,
-1040956821,
-787665626,
-520977881,
-245429388,
34293346,
313432823,
587241461,
851062346,
1100408434,
1331038870,
1539031109,
1720847638,
1873396136,
1994082072,
2080852829,
2132232618,
2147347576,
2125940628,
2068375863,
1975632336,
1849287422,
1691489985,
1504923830,
1292762058,
1058613099,
806459337,
540589384,
265525133,
-14055147,
-293396379,
-567747550,
-832442518,
-1082979375,
-1315097011,
-1524847589,
-1708663688,
-1863418980,
-1986481400,
-2075757913,
-2129730112,
-2147480042,
-2128705814,
-2073726737,
-1983477893,
-1859494225,
-1703884437,
-1519295127,
-1308865774,
-1076175344,
-825181414,
-560152869,
-285597292,
-6184300,
273333873,
548203208,
813748749,
1065454120,
1299038338,
1510528622,
1696327964,
1853276304,
1978704277,
2070478616,
2127038431,
2147421756,
2131281915,
2078893412,
1991147266,
1869535856,
1716127539,
1533531471,
1324853229,
1093641997,
843830194,
579666598,
305644083,
26423199,
-253247089,
-528610172,
-794982697,
-1047834225,
-1282864277,
-1496075482,
-1683841563,
-1842969009,
-1970751394,
-2065015408,
-2124157814,
-2147172725,
-2133668704,
-2083875427,
-1998639773,
-1879411424,
-1728218205,
-1547631598,
-1340723004,
-1111011506,
-862404019,
-599128838,
-325663725,
-46659750,
233137810,
508970181,
776146031,
1030121255,
1266576264,
1481489452,
1671205593,
1832498011,
1962623458,
2059368772,
2121088517,
2146732968,
2135865968,
2088672340,
2005954750,
1889120053,
1740155361,
1561594255,
1356473687,
1128282329,
880901241,
618537860,
345654439,
66892157,
-213007822,
-489284981,
-757240423,
-1012316784,
-1250175747,
-1466771827,
-1658421177,
-1821864240,
-1954321190,
-2053539212,
-2117830813,
-2146102527,
-2137873512,
-2093283725,
-2013091547,
-1898660878,
-1751937947,
-1575418203,
-1372103880,
-1145452931,
-899320216,
-637891939,
-365614450,
-87118622,
192858913,
469556320,
738267552,
994422393,
1233664182,
1451923916,
1645489450,
1811068640,
1945845328,
2047527244,
2114384991,
2145281456,
2139691157,
2097709173,
2020049529,
1908033054,
1763564914,
1589102213,
1387612196,
1162521788,
917659309,
657189357,
385541985,
107337348,
-172692874,
-449785950,
-719229105,
-976439672,
-1217043036,
-1436947036,
-1632411562,
-1800112171,
-1937196625,
-2041333403,
-2110751356,
-2144269830,
-2141318743,
-2101948290,
-2026828078,
-1917235747,
-1775035232,
-1602645069,
-1402997255,
-1179487383,
-935916889,
-676428400,
-405435275,
-127546540,
152511495,
429975627,
700126771,
958370217,
1200313785,
1421842518,
1619188673,
1788995805,
1928375849,
2034958239,
2106930233,
2143067736,
2142756125,
2106000700,
2033426593,
1926268140,
1786347881,
1616045570,
1418257692,
1196348209,
954091336,
695607359,
425292551,
147744403,
-132316569,
-410127112,
-680962247,
-940215635,
-1183477915,
-1406611703,
-1605821959,
-1777720531,
-1919383783,
-2028402319,
-2102921960,
-2141675283,
-2144003175,
-2109866042,
-2039844487,
-1935129431,
-1797501857,
-1629302524,
-1433392152,
-1213102768,
-972181035,
-714724530,
-445112050,
-167929143,
112109890,
390242166,
661737237,
921977537,
1166536922,
1391255946,
1592312606,
1766287349,
1910221227,
2021666224,
2098726893,
2140092594,
2145059782,
2113543975,
2046081191,
1943818832,
1808496168,
1642414754,
1448399289,
1229749572,
990184379,
733778214,
464892012,
188098965,
-91893252,
-370322557,
-642453448,
-903657544,
-1149492310,
-1375776608,
-1578661815,
-1754697275,
-1900888993,
-2014750553,
-2094345406,
-2138319810,
-2145925852,
-2117034170,
-2052136150,
-1952335572,
-1819329837,
-1655381095,
-1463277771,
-1246287143,
-1008099770,
-752766721,
-484630679,
-208252080,
71668452,
350370054,
623112592,
885257283,
1132345594,
1360175067,
1564870798,
1742951339,
1891387912,
2007655920,
2089777886,
2136357087,
2146601309,
2120336317,
2058008826,
1960678895,
1830001904,
1668200395,
1478026276,
1262714012,
1025925615,
771688362,
504326299,
228386697,
-51437287,
-330386429,
-603716387,
-866778388,
-1115098296,
-1344452707,
-1550940780,
-1731050584,
-1881718827,
-2000382955,
-2085024740,
-2134204601,
-2147086092,
-2123450124,
-2063698698,
-1968848058,
-1840511418,
-1680871517,
-1492643495,
-1279028719,
-1043660331,
-790541457,
-523977121,
-248501027,
31201552,
310373457,
584266557,
848222501,
1097751949,
1328610925,
1536872998,
1718996067,
1871882596,
1992932305,
2080086390,
2131862543,
2147380159,
2126375315,
2069205260,
1976842337,
1850857449,
1693393333,
1507128128,
1295229815,
1061302344,
809324332,
543581401,
268593284,
-10963046,
-290332916,
-564764829,
-829591270,
-1080308093,
-1312651128,
-1522668703,
-1706788859,
-1861880094,
-1985304631,
-2074963275,
-2129331120,
-2147483482,
-2129111628,
-2074528023,
-1984661022,
-1861039075,
-1705764733,
-1521478889,
-1311315862,
-1078850085,
-828035318,
-563137397,
-288661682,
-9276435,
270266586,
545212936,
810886350,
1062768278,
1296574733,
1508329155,
1694430044,
1851712209,
1977500611,
2069655850,
2126610558,
2147396054,
};
