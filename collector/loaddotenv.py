# Loads env vars from .env
# based on https://stackoverflow.com/questions/62314497/access-of-outer-environment-variable-in-platformio
Import("env") # this is some serious bullshit
from os.path import isfile
from pydoc import splitdoc

assert isfile(".env")

try: 
    e = open(".env", "r")
    s = open("./src/dotenv.h", "w")
    
    content = "#pragma once\n\n"
    
    lines = e.readlines()
    for line in lines:
        splits = line.strip().split("=")
        if (len(splits) <= 1): continue
        
        name = splits[0]
        value = "".join(line.strip().split("=")[1:]).strip("\"")
        
        content += "#define {} \"{}\"\n".format(name, value)
    s.write(content)
except IOError:
    print("File .env or secrets.h not accessible",)
finally:
    e.close()
    s.close()
