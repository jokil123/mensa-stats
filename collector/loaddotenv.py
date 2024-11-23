# Loads env vars from .env
# based on https://stackoverflow.com/questions/62314497/access-of-outer-environment-variable-in-platformio
Import("env") # this is some serious bullshit
from os.path import isfile

assert isfile(".env")

try:
    f = open(".env", "r")
    lines = f.readlines()
    envs = []
    for line in lines:
        name = line.strip().split("=")[0]
        value = "".join(line.strip().split("=")[1:]).strip("\"")
        envs.append("-D{}=\"{}\"".format(name, value))

    print(envs)
    env.Append(BUILD_FLAGS=envs)
except IOError:
    print("File .env not accessible",)
finally:
    f.close()
