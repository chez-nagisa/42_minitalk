# minitalk  

`minitalk` is a 42 project that focuses on inter-process communication (IPC) using UNIX signals.  
The goal is to implement a client-server system where the client sends a string message to the server **bit by bit**, using only `SIGUSR1` and `SIGUSR2`.

## 🧠 What I Learned

- Inter-process communication using signals
- Encoding characters into binary and transmitting them one bit at a time
- Signal handling in C with `signal()` and `sigaction()`
- Synchronization and timing in single-threaded environments

## 🧪 How to Use

```bash
# 1. Compile both server and client
make

# 2. Run the server
./server
# → It will output a PID like: PID: 12345

# 3. In another terminal, run the client
./client 12345 "Hello, world!"
```

---

# minitalk（日本語）

`minitalk` は、UNIXのシグナルを使って**プロセス間通信（IPC）を自分で実装する**42の課題です。  
クライアントが文字列を**ビット単位でサーバに送信**し、サーバがそれを受け取って表示します。  
使用できる通信手段は `SIGUSR1` と `SIGUSR2` のみです。

## 🧠 学んだこと

- `kill()` を用いたシグナルベースのプロセス間通信
- 文字をビット単位にエンコードし、逐次送信する仕組み
- `signal()` / `sigaction()` によるシグナルハンドリング
- マルチプロセス環境におけるタイミング・同期の考え方

## 🧪 使い方

```bash
# 1. サーバとクライアントを make でビルド
make

# 2. サーバを起動（PIDが表示されます）
./server
# 例: PID: 12345

# 3. 別ターミナルでクライアントを起動（PIDと送る文字列を指定）
./client 12345 "Hello, world!"
```
