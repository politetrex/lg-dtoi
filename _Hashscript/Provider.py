import hashlib

# For example, advcpp_3.zip
Filename = "迷雾行动 1.0 （迷宫 5.1）.cpp"

# For example, Fri 5 Jun, 2026 18:58
Time = "Fri 5 Jun, 2026 18:58"

result=hashlib.sha256(bytes(Filename+Time,"Utf-8")).hexdigest()

print(result)