# 0. compile c
gcc redirect_stdin.c -o redirect_stdin

# 1. จาก keyboard (พิมพ์เอง กด Ctrl+D เพื่อจบ)
echo -e 'Press any key.... \nTo exit press Ctrl+D to terminate program'
./redirect_stdin

# 2. จากไฟล์
./redirect_stdin < input.txt

# 3. จาก pipe (output ของโปรแกรมอื่นมาเป็น stdin)
echo "hello world" | ./redirect_stdin
cat input.txt | ./redirect_stdin