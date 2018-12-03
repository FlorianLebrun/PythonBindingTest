import python_toy
import os

try:
    print(python_toy.myMethod("tt"))
except Exception as e:
    print("Unexpected error:", e)

os.system("pause")
