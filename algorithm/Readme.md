### 编译

- release版本
``` bash
cd build
chmod +x mkapp.sh
chown -R paas:paas ..
./mkapp.sh
```

- debug版本
``` bash
cd build
chmod +x mkapp.sh
chown -R paas:paas ..
./mkapp.sh -d
```

### 排序算法

- 冒泡排序
- 选择排序
- 插入排序
- 希尔排序
- 快速排序
- 归并排序
- 堆排序
- 基数排序
- 横排序

### 测试结果

```
==================run llt start=====================
release version.
Test sorting algorithm:

arr[size: 10, num: 100000]
┌──────────────┬──────┬──────┐
│     name     │result│ cost │
├──────────────┼──────┼──────┤
│   sort_quick1│  OK  │     2│
├──────────────┼──────┼──────┤
│    sort_quick│  OK  │     3│
├──────────────┼──────┼──────┤
│    sort_shell│  OK  │     2│
├──────────────┼──────┼──────┤
│    test_qsort│  OK  │     3│
├──────────────┼──────┼──────┤
│sort_insertion│  OK  │     3│
├──────────────┼──────┼──────┤
│   sort_bubble│  OK  │     3│
├──────────────┼──────┼──────┤
│  sort_bubble1│  OK  │     2│
├──────────────┼──────┼──────┤
│  sort_bubble2│  OK  │     4│
├──────────────┼──────┼──────┤
│sort_selection│  OK  │     2│
└──────────────┴──────┴──────┘

arr[size: 100, num: 10000]
                name               result             costTick
         sort_quick1                   OK                    3
          sort_quick                   OK                    4
          sort_shell                   OK                    5
          test_qsort                   OK                    6
      sort_insertion                   OK                    9
         sort_bubble                   OK                   15
        sort_bubble1                   OK                   14
        sort_bubble2                   OK                   13
      sort_selection                   OK                   13

arr[size: 1000, num: 1000]
                name               result             costTick
         sort_quick1                   OK                    4
          sort_quick                   OK                    5
          sort_shell                   OK                    7
          test_qsort                   OK                   10
      sort_insertion                   OK                   69
         sort_bubble                   OK                   77
        sort_bubble1                   OK                   82
        sort_bubble2                   OK                  117
      sort_selection                   OK                  123

arr[size: 10000, num: 100]
                name               result             costTick
         sort_quick1                   OK                    5
          sort_quick                   OK                    7
          sort_shell                   OK                   12
          test_qsort                   OK                   10
      sort_insertion                   OK                  657
         sort_bubble                   OK                 1299
        sort_bubble1                   OK                 1345
        sort_bubble2                   OK                 1592
      sort_selection                   OK                 1222

arr[size: 100000, num: 10]
                name               result             costTick
         sort_quick1                   OK                    7
          sort_quick                   OK                    8
          sort_shell                   OK                   14
          test_qsort                   OK                   10
      sort_insertion                   OK                 6401
         sort_bubble                   OK                15556
        sort_bubble1                   OK                16502
        sort_bubble2                   OK                16969
      sort_selection                   OK                12751

==================run llt end=====================
```
