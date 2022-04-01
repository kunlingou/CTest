### 使用方法

- 1. 编译：
```
gcc test_socket.c -lpthread -o test_socket -g
chmod +x test_socket
```
- 2. 执行：
```
启动server：
./test_socket server

启动client:
./test_socket client &
./test_socket client &
```