from python_toy import python_toy
import os

try:
  print(python_toy("tt"))
except Exception as e:
  print("Unexpected error:", e)

os.system("pause")
