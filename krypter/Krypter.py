from cryptography.fernet import Fernet
import subprocess
from tkinter import *
import sys


# Current Support for files of type: .jpg, .png, .pdf, .py

MODE = sys.argv[1]
FILE  = sys.argv[2]


# ------------------------------ Encryption Class ------------------------------ #


class Encrypt:
    cap = b''
    passkey = b''
    crypted_bytes = b''


    def encrypt_bin(bytes):
        key = open("/Users/nate_g/Desktop/Coding/Projects/Krypter_App/key.key", "rb").read()
        f = Fernet(key)
        crypted = f.encrypt(bytes)
        Encrypt.crypted_bytes += crypted


    def add_cap(ext):
        if ext == "jpg":
            Encrypt.cap = b'#it1'
        elif ext == "png":
            Encrypt.cap = b'#it2'
        elif ext == "pdf":
            Encrypt.cap = b'#wd1'
        elif ext == "py":
            Encrypt.cap = b'#ps1'


    def add_passkey(code):
        try:
            int(code)
        except ValueError:
            print("The passkey must be 4 digits")
            Encrypt.add_passkey()

        code = str(code)
        if len(code) > 4:
            print("Passkey must be no longer than 4 digits")
            Encrypt.add_passkey()
        elif len(code) < 4:
            print("Passkey must be no less than 4 digits")
            Encrypt.add_passkey
        else :
            code = int(code)
            code = code.to_bytes(4, 'little')
            Encrypt.passkey += code


    def create_file(name):
        user = subprocess.getoutput("whoami")
        f_path = f'/Users/{user}/Desktop/'
        new_file = open(f"{f_path}/{name}.crypt", 'wb')
        new_file.write(Encrypt.cap)
        new_file.write(Encrypt.passkey)
        new_file.write(Encrypt.crypted_bytes)


    def Main():
        path = FILE
        passkey = input("Enter a passkey: ")

        split = path.split(".")
        ext = split[1]

        s_exs = ["jpg", "png", "pdf", "py"]

        if not ext in s_exs:
            print("File format not supported. Please try again.")
        else :

            try:
                file = open(path, 'rb')
            except FileNotFoundError:
                print("File not found. Check file name and extension and try again.")
            else :

                name = input("Enter a new name for the encrypted file: ")

                data = file.read()
                Encrypt.encrypt_bin(data)
                Encrypt.add_cap(ext)
                Encrypt.add_passkey(passkey)
                Encrypt.create_file(name)
                file.close()

                Encrypt.cap = b''
                Encrypt.passkey = b''
                Encrypt.crypted_bytes = b''

                subprocess.getoutput(f"rm -r {path}")

                print("Encryption Complete")
        

# ------------------------------ Decryption Class ------------------------------ #


class Decrypt:
    decrypted_bytes = b''
    auth = False


    def authenticate(passkey):
        code = int.from_bytes(passkey, "little")
        code = str(code)
        usercode = input("Enter the passkey for this file: ")
        if usercode == code:
            Decrypt.auth = True
            print("Authentication Complete\n Decrypting...")


    def decrypt_bin(bytes):
        key = open("/Users/nate_g/Desktop/Coding/Projects/Krypter_App/key.key", "rb").read()
        f = Fernet(key)
        decrypted = f.decrypt(bytes)
        Decrypt.decrypted_bytes += decrypted


    def find_ext(cap):
        if cap == b'#it1':
            ext = "jpg"
        elif cap == b'#it2':
            ext = "png"
        elif cap == b'wd1':
            ext = "pdf"
        elif cap == b'ps1':
            ext = "py"

        return ext


    def create_file(ext, name):
        user = subprocess.getoutput("whoami")
        f_path = f'/Users/{user}/Desktop/'
        new_file = open(f"{f_path}/{name}.{ext}", 'wb')
        new_file.write(Decrypt.decrypted_bytes)


    def Main():
        path = FILE

        split = path.split(".")
        ext = split[1]

        if not ext == "crypt":
            print("File format not supported. Decrypt command only supports files of type '.crypt'. Please try again.")
        else :

            try:
                file = open(path, 'rb')
            except FileNotFoundError:
                print("File not found. Check file name and extension and try again.")
            else :
                cap = file.read(4)
                ext = Decrypt.find_ext(cap)
                passkey = file.read(4)
                Decrypt.authenticate(passkey)

                if Decrypt.auth == True:
                    name = input("Enter a new name for the decrypted file: ")
                    
                    data = file.read()
                    Decrypt.decrypt_bin(data)
                    Decrypt.create_file(ext, name)
                        
                    file.close()

                    Decrypt.decrypted_bytes = b''

                    subprocess.getoutput(f"rm -r {path}")

                    print("Decryption Complete")

                else :
                    print("Authentication failed")


command = MODE

if command == 'encrypt':
    Encrypt.Main()

elif command == 'decrypt':
    Decrypt.Main()

else :
    print("Krypter: Not a valid command.")

