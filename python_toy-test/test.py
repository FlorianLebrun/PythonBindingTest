import python_toy
import os

try:
    print(python_toy.myMethod("tt", 12))
except Exception as e:
    print("Unexpected error:", e)

os.system("pause")
