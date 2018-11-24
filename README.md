# Topic

This is an exam project from TREVI Tech CO., LTD.

The goal of the program in short is to find keywords in a text string.

In this project, i had implemented three algorithms for pattern searching and a multithreading parser for parallel computing. It can easily to add other algorithms in this program architecture. Furthermore, it can also easily to add other parallel computing features to reduce the time consumption.

The default keyword storage is using a single file. It can add other storages such as SQL or Redis database etc.

I will keep doing those implementations if some condition allows.


# Build Project
Using cmake and GNU make tools.

# Usage
#### Show Help:
    $ ./trevi-filter -h

#### Add Keywords:
    $ ./trevi-filter -a key1 key2 'i am key3'

#### List Keywords:
    $ ./trevi-filter -l

#### Clear Keywords:
    $ ./trevi-filter -c

#### Parse text (using -f option to choose an algorithm):
    Using Default(Std-String) algorithm
    $ ./trevi-filter -p 'i am text string'

    Using Native algorithm
    $ ./trevi-filter -f 1 -p 'i am text string'

    Using KMP algorithm
    $ ./trevi-filter -f 2 -p 'i am text string'

#### Multithreading Parser (using -t option to choose thread count)
    Using multithreading parser with Default algorithm
    $ ./trevi-filter -t 2 -p 'i am text string'

    Using multithreading parser with Native algorithm
    $ ./trevi-filter -t 2 -f 1 -p 'i am text string'

    Using multithreading parser with KMP algorithm
    $ ./trevi-filter -t 2 -f 2 -p 'i am text string'


# Test
Test Case https://docs.google.com/spreadsheets/d/18FYYUl6OMbvJI6XBpAqR3OZ88KVcmpewQnA_tMxnbOc/edit?usp=sharing

# TODO List
* keyword duplicate checking.
* keyword tool to build large data of keywords.
* Other pattern searching algorithms.
* Other parallel computing features.
* 紀錄實作所使用之資料結構及演算法
* 對其實作之時間及空間複雜度進行推導和分析
* test case 包含 200K 個以上長度不等的不完全重複關鍵詞，過濾時輸入長度為 100 左右的句子進行測試
* 圖像化或表格化呈現其運算效能
* 包含測試結果如何計算、分佈性質、信賴區間...等分析參數
* 盡可能優化其記憶體使用量
* 更多您發揮創意想到的功能

# Special Thanks
GitHub project : jarro2783/cxxopts https://github.com/jarro2783/cxxopts
This is a powerful and easy to use library of command line option parser. It saved me a lot of time.
