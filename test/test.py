from hello import hello
import os

try:
  print(hello("tt"))
except Exception as e:
  print("Unexpected error:", e)

os.system("pause")
