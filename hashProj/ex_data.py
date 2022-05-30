from Crypto.Hash import SHA256
from Crypto.Hash import MD5
import hashlib
import random
import string

# Unsalted Hashes

hash_nosalt = [\
   '2055c34950486290b60268aefb586edc8877e2294edd52a86614a8984f40a8fb',\
   'ca2e89b1f92c980df25543a423500466e08888485711de352f4f892c704198c1',\
   '8c414fd826c961685aeacb57aec8e1154a029a58bab88ab33a14751c3b8386f2',\
   '94309e4772adec972000e4b28efc83208eea13e7b5dddcbb27ff88a2d3da7248',\
   'bdc326dbf5c0ab5238db6e208a4537f7ab6b548723fc0bc945cbc8fcd26a8d6a',\
]

# Salted Hashes

hash_salted = [\
   '38087:e0b869e99b57dec36a2a013d3b04eb286e4ccf1a054a0a029811f25b5cd75ca5',\
   '81933:d531515735375e11c536d6de95d8b781d68b72fe1714f3f802f4eec1a22b004e',\
   '54342:b061e304a9e8534b7dfe7dd75d12abcd72d1e8bb730cc8d0ec772ff6c6bb4d62',\
   '22517:848b261753883417d4a291288ee38507abcabd7a7e21f280653ea0ba0f8e047f',\
   '57281:08301510d6bc7bfea68272bacbaf5ce120366d17d0b0aa9bcf9c1245f03abd97',\
   '92148:c260cfe88a1ca4d5edac7850fdc5d2c7bc67130f788a5b311e05c7f57ff27fb8',\
]

# Hashes of Five-character Random Passwords

hash_rand = [\
   '5d7af6be8e7ab47467dc87b2470e16cc8fe6986c40537936d5cdc868b3c2d51b',\
   '10ff81984bb4fd2f62cae3859fe7d74fb7293b5ef7198042428a1d0482763f29',\
   '605f5e4d916e03a87347aa9ca40b398251a59b2a689632fffca74ec9a6c95c5e',\
   'bb40fbbce3740533f3491da37239a2dcc4c062f39c781baf0932369e967b3998',\
   'fb741c071bb5ed5cab838bf3f46a50cff17f23ecdebcbd7b5a8458b8d421f71b',\
   '1604d5ebd17cad1fc79a1206473429796c8d90b76f07b1eb5b04869d83c9a44f',\
   'dea2e0a21e0d90e63e8a2a02586bc0e9e1e8feb64e975d835aabdd9d550a48e6',\
   '185db25b849a2535541c219f9a9df3c8d8a8f9a141f9d20f0902f15faa7fd6a3',\
   '3c521d6e4870c3783d0bcc49a68c30fb726816aeb8b72af6a44328d1a0e8d7a4',\
   'e37ce1fdde23ec6b8187caed23efcec3483215d10caa5cd488ecc89fba29445a',\
   '1d9304443d89fc8804e4fcb45a4292a5c8ecd6e7522de0c65c4a4c583c0e989b',\
   'b4de597fa7ee6e5a1aafdbe4f610f44e5917f24555bd134e2dc3b54926fc5688',\
   '658082bfbc45e61d6d078170f9b09c6f7f04b8f5e4a87c3199bba7ff64891a20',\
   '220e3de048e58de267a0ce45388cc51b7006fa359267278b1e46290452ebcd87',\
   'e70fceb6c4dacced90d61ed6b7ea5aede791855ef126c213551034410aa7c052',\
   '09b590c61eb30adbb2316e1e7187d9b6be8022792a8fac852082ac0e34e71bdb',\
   '040cfac289fffeb5aa2b0202da0851371e99f4433b58d81063a526d20e761720',\
   '7f5b2827fab52b8e6d99d6e5f1a63eab26a0c45930a7553a914999a24a6c9fa8',\
   '9189c838f9628e089fc202409e6e7e724a2e2d8305fd12575ba2ab606b253801',\
   '287e899c2d582c5e97b9d292263a555c3f7ca091211d6d6cbdd8a40c2c388b28',\
   'f71d6bb069f4da310cd50c1bf3aa72430a1c337743080b276b9feaa2f2fa6d93',\
   'a28608138cb932b81f2c4af1b313419ce1290366195eea6bc2ee7835919600d1',\
   '6e22c6426697b85c84f54431e057b416e3a081b8917b9cc72cbc87a6642f0165',\
   'ea21f3ffb10c32ffb5f4b51c4d38f4bc6c9c0275cdb45a2cca30f14e1c3e81c3',\
   '5b289f88ef6a94e01b3afc19689069461dc481099fbb21de7caeac082cf72b20',\
   'a40407b85632243158739b6f9b04d453d2f8ad5b1f2a70fe8127eaf0c6411d1b',\
   'bf710df7c70f0d4ee06506ed28ea3ac610ae8953eaa1d8d45e968c4d6d9a0955',\
   '5783d38e7c1bfff74255bd781f81a1d24346320984701a7ffec24008ffd01205',\
   'ba204a52bd99db092c80b3597d5c8c44d51db73e85b3d41b0353d209752ace7f',\
   '2f9296215b8f7b1de1926be39650136bbea07d5d334faa8799fbb25f9233d3bf',\
   '2c8fa639a865fdcfa8a343d5bd254d8f2dcb17756e63c6db9dc5ac07d3f152fa',\
   '63e50a725f6ee805110ee2b39b1d020532745349a4d9bcb07f921e25792fb92b',\
   '24a06619390dc056b06a7b26e488573dee2c73998fdaae4257bcfcc58533b422',\
   'f08a3b8da4b7e0c2a202f7fb852a9bd5102d3f173e2af5536e9ab249663efb5f',\
   'ea6260f448b42dd56b01a042ad0e62bee3981253a82cf6358d9b2987ab4e61b1',\
   '260882a1e0e0ef85216bb7f8360e2380cf50c9d049da293b758e6f448a8089dc',\
   '13c70f5ae0d3f77de84ce80fed9d2394d739c2d7fc44cbc4fec9fb8c8842806f',\
   '0980b7f78f23311f39051ae446e50ec6edf70b0214a77f26d93737b17898313f',\
   '356d6cf11a472f330d7459af79d3b6432bcea42dc1470c6de5f6fd7432669c4a',\
   '141a2f41176f165be0cf194835f092e4c2ff1524a27726b34d2021d1ff881bb3',\
   'ae85e8ef36c1a8d57a20a32b110812921d2dd067b5086c3e292a43fefe158ddb',\
   '0642505800901ac234c02599ec6e4a956e1c38e24739f0125cd87bd1ed8c7072',\
   'b132e84763654848033d7416db001badc607579fe3fda9ecb2e6e7bfeb18d306',\
   '4e117e1a696f9f431cc9f4d9db9a74d788185505a1c33f17cfcf8c781cf8180a',\
   'a839f30eecb8d5841f1a41d9697fa178e20b1c6c891247337b9d9dc73138df4c',\
   '3cd82f0526c1c19cd4a6b894d96e6ec16d48bfdd1e95497b247b0b4846501f08',\
   'ebe7e734801aea6741bfc7a3cfb960b7530faaa172418290c02c908f5637a68d',\
   '4fcf027c0220d5db40587732beeaaf30f63e98333821ff2f7d23ab9c50131c0c',\
   '8eabfcc69c38718e739c28c4ad968024b766a49b7499570336c4fb9d826b0ec8',\
   'eb28d9f20cd59f954b7808c04dea061e68e65d30534c33b4f344aa20935718e7',\
]


# Exercise 1:

ex1_hash = '4f59a144a9c2d932f95a3c6160698c5f'

# Exercise 2:

ex2_hashes = ['root:c44a8bae970ecc11fb01d11be9886377c1ac9b8d2ff450d5ebefc5b78eaa95ef', \
	          'sam:95c0d6e7a0e1ecf1dbd33ed89fedff8b1ffb3dbfb7c6288a6c47f0bec35e3124', \
              'topha:2415224ff13cef4a85213e06958fa0c5393e83fb631bf75c4fc38773e4fea1f5', \
              'sally:035440b51fb1a8a4f910567d9f7292f6fb55230f037cf0be7b8c16c649e416da']

# Exercise 3:

ex3_hashes = ['root:6954222:d98f1c1410daefd5a7efa893ae7bf237', \
              'sam:1258244:e8c101595f2701d59626b68d9368b592', \
              'topha:11030922:40f1b3e282ca6f3a4f53a856d742760b', \
              'sally:13064284:75b363a560580edc76b0451c2b3a6e8b']


pwd = '4f59a144a9c2d932f95a3c6160698c5f';

sha = hashlib.sha256(pwd.encode())
md = hashlib.md5(pwd.encode())


#exercise 1
print('Exercise 1: ')

infile = open('rockyou.100000.txt')

for line in infile:
    line = line.rstrip('\n')

    hashline = hashlib.md5(line.encode())
    if(hashline.hexdigest() == pwd):
        print('Admin password: ' + line)


print('Exercise 2: ')
infile = open('rockyou.100000.hash')

pwtable = {}

for line in infile:
    fields = line.rstrip('\n').partition(' ')

    pwtable[fields[0]] = fields[2]

targetArr = []
pwArr = []
for x in range(4):
    pw = ex2_hashes[x]
    pw = pw[0:].split(':')
    pwArr.append(pw[1])

for x in range(4): 
    if pwArr[x] in pwtable:
        print('Password :' + pwtable[pwArr[x]])

print('Exercise 3: ')

saltArr = []
pwArr = []

infile = open('rockyou.100000.txt', 'r')

for x in range(4):
    pw = ex3_hashes[x]
    pw = pw[0:].split(':')
    saltArr.append(pw[1])
    pwArr.append(pw[2])

for line in infile:
    line = line.rstrip('\n')
    for x in range(4):
        saltline = saltArr[x]+line
    
        md5 = hashlib.md5(saltline.encode())

        if md5.hexdigest() in pwArr:
            print('Password is: ' + line + '\n')
    
print('Assignment: ')
print('UnSalted: ')
infile = open('rockyou.100000.hash')

pwdict = {}

for line in infile:
    fields = line.rstrip('\n').partition(' ')

    pwdict[fields[0]] = fields[2]

for i in hash_nosalt:
    if i in pwdict:
        print(pwdict[i])

print('Salted: ')
count = 0
saltArr = []
lineArr = []
infile = open('rockyou.100000.txt', 'r')

for i in hash_salted:
        salttemp = i
        salt = salttemp[0:5]
        saltArr.append(salt)
        password = salttemp[6:]
        lineArr.append(password)

for line in infile:
    line = line.rstrip('\n')
    for x in range(6):
        saltline = saltArr[x]+line
    
        sha = hashlib.sha256(saltline.encode())


        if(sha.hexdigest() == lineArr[x]):
            print('Password is : ' + line)


#This code takes the 5 letter version of the RockYou passwords and checks them
#Then it generates 1999999 random 5 letter strings and tests them
infile = open('rockyou.100000.hash')

print('Random: ')
pwdict = []

for line in infile:
    fields = line.rstrip('\n')

    fields = fields.split(' ')
    fields = fields[1]
    fields = fields[0:5]
    pwdict.append(fields)
    sha = hashlib.sha256(fields.encode())
    if sha.hexdigest() in hash_rand:
        print(line)

pwdict = []
randArr = []

for x in range(1999999):
    randString = ''.join(random.choice(string.ascii_lowercase + string.digits + string.ascii_uppercase) for i in range(5))
    sha = hashlib.sha256(randString.encode())
    pwdict.append(sha.hexdigest())
    randArr.append(randString)

count = 0
for i in hash_rand:
    for t in pwdict:
        if i == t:
            print(randArr[count])

    count+=1
            
'''
for line in infile:

    line = line.rstrip('\n')
    saltline = salt+line

    
    sha = hashlib.sha256(saltline.encode())
    
    #saltArr.append(sha.hexdigest())
    lineArr.append(line)
    
    count = 0
    for i in hash_salted:
        salttemp = hash_salted[count]
        saltPw = salttemp[0:5] + salttemp[6:]
        salted = hashlib.sha256(salttemp.encode())

        line = line.rstrip('\n')
        saltline = salttemp[0:5]+line

    
        sha = hashlib.sha256(saltline.encode())
    
        #saltArr.append(sha.hexdigest())
        lineArr.append(line)
        
        #print('Password: ' + line + 'Salted RockYou: ' + sha.hexdigest() + 'Salted Password: ' + salted.hexdigest())
        if sha.hexdigest() == salted.hexdigest():
            print('wow')
        count+=1
'''
#for i in hash_salted:
 #   for t in saltArr:
  #      if saltArr[t] == lineArr[t]:
   #         print(saltArr[t])
#print(saltPw)
            

    
