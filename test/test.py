from hello import hello, Classy
import os

try:
  c = Classy(4)
  print(c.goody)
  print(c.miami())
  print(c.new_york)
  print(hello("tt"))
except Exception as e:
  print("Unexpected error:", e)

os.system("pause")
