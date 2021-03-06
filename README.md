# Mind_Monitor
A comparison of various C Programming memory debuggers

## MEMORY DEBUGGERS

* Dmalloc
* Electric Fence
* Valgrind
* Memwatch
* Mtrace

## DEPENDENCIES

From the `Mind_Monitor` directory:
`devops/script/dependency_checker.sh`

| Tool           | Verify                             | Install                             |
| :------------: | :--------------------------------- | :---------------------------------- |
| Dmalloc        | `dmalloc --version`                | `apt install libdmalloc*`           |
| Electric Fence | `dpkg-query --list electric-fence` | `apt install electric-fence`        |
| Valgrind       | `valgrind --version`               | `apt install valgrind`              |
| Memwatch       | `ls src/memwatch.?`                | `devops/script/install_memwatch.sh` |
| Mtrace         | `mtrace --version`                 | Built into glibc                    |

## RUN TESTS

From the `Mind_Monitor` directory:
`devops/script/test_all.sh`

## TEST RESULTS

| Filename     | Description               | Dmalloc                         | Electric Fence           | Valgrind                 | Memwatch           | Mtrace     |
| :----------- | :------------------------ | :-----------------------------: | :----------------------: | :----------------------: | :----------------: | :--------: |
| bad_code1.c  | Uninit. mem               | :x::anger:                      | :x:                      | :heavy_check_mark:       | :x:                | :x: |
| bad_code2.c  | Buffer overflow           | :heavy_check_mark::anger::boom: | :x:                      | :heavy_check_mark:       | :heavy_check_mark: | :x: |
| bad_code3.c  | Memory leak               | :heavy_check_mark::anger:       | :x:                      | :heavy_check_mark:       | :heavy_check_mark: | :heavy_check_mark: |
| bad_code4.c  | Invalid mem access        | :x::anger:                      | :x::boom:                | :heavy_check_mark:       | :x:                | :x: |
| bad_code5.c  | Double free               | :heavy_check_mark::anger::boom: | :heavy_check_mark::boom: | :heavy_check_mark:       | :heavy_check_mark: | :x: |
| bad_code6.c  | Uninit. integer           | :x::anger:                      | :x:                      | :heavy_check_mark:       | :x::anger:         | :x: |
| bad_code7.c  | Overlapping memcpy        | :x::anger:                      | :x:                      | :x:                      | :x:                | :x: |
| bad_code8.c  | Fishy malloc values       | :heavy_check_mark::anger::boom: | :heavy_check_mark::boom: | :heavy_check_mark::boom: | :x::boom:          | :x::boom: |
| bad_code9.c  | Fishy calloc values       | :heavy_check_mark::anger::boom: | :x::boom:                | :heavy_check_mark::boom: | :x::boom:          | :x::boom: |
| bad_code10.c | Multi-process memory leak | :heavy_check_mark::anger:       | :x:                      | :x:                      | :heavy_check_mark: | :heavy_check_mark: |
| bad_code11.c | Multi-process double free | :x::anger:                      | :heavy_check_mark:       | :x:                      | :heavy_check_mark: | :x: |
| bad_code12.c | Multi-thread memory leak  | :heavy_check_mark::anger:       | :x:                      | :heavy_check_mark:       | :heavy_check_mark: | :heavy_check_mark: |
| bad_code13.c | Multi-thread double free  | :heavy_check_mark::anger:       | :heavy_check_mark:       | :heavy_check_mark:       | :heavy_check_mark: | :heavy_check_mark: |

**LEGEND**

| Emoji              | Meaning                                    |
| :----------------: | :----------------------------------------- |
| :anger:            | False positive, misleading/missing results |
| :boom:             | Seg fault or core dump                     |
| :grey_question:    | Test not yet executed                      |
| :heavy_check_mark: | Succeeded in finding the error             |
| :x:                | Failed to find the error                   |

NOTES:

	- Some ideas came from https://valgrind.org/docs/manual/mc-manual.html
	- Bad Code 10 is the multi-process version of Bad Code 3
	- Bad Code 11 is the multi-process version of Bad Code 5
	- Bad Code 12 is the multi-thread version of Bad Code 3
	- Bad Code 13 is the multi-thread version of Bad Code 5

## CONCLUSION

### Errors Found

* Dmalloc - 8/13
* Electric Fence - 4/13
* Valgrind - 10/13
* Memwatch - 7/13
* Mtrace - 4/13

### Ease Of Use

On a scale of 1 to 5 (5 being the easiest to use):

* Dmalloc - 2/5
* Electric Fence - 3/5
* Valgrind - 4/5
* Memwatch - 3/5
* Mtrace - 3/5

### Readable Output

On a scale of 1 to 5 (5 being the easiest to read):

* Dmalloc - 2/5
* Electric Fence - 4/5
* Valgrind - 3/5
* Memwatch - 5/5
* Mtrace - 5/5

### Final Ranking

Ranked best to worst:

1. Valgrind (72.3%)
1. Memwatch (71.3%)
1. Mtrace (63.6%)
1. Electric Fence (56.9%)
1. Dmalloc (47.2%)
