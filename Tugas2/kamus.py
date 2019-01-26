class Kamus:
    
    def __init__(self, word=''):

        
        if word == '':
            self.left = None
            self.right = None
            self.data = None
        
        elif len(word) == 1:
            self.left = None
            self.right = None
            self.data = word
        
        else:
            self.right = None
            self.data = word[0]
            self.left = Kamus(word[1:]) 

    def add(self, word):
        if ord(word[0]) > ord(self.data):
            if self.right is None:
                self.right = Kamus(word)
            else:
                self.right.add(word)
        elif ord(word[0]) < ord(self.data):
            right = self.right
            left = self.left

            self.right = Kamus(self.data)
            self.left = Kamus(word[1:])
            self.data = word[0]

            self.right.left = left
            self.right.right = right
        else:
            # if len(word[1:]) > 1:
            if self.left is None:
                self.left = Kamus(word[1:])
            else:
                self.left.add(word[1:])
            # else:
            #     self.left = Kamus(word[1:])

    def getDeep(self):
        deep = 0
        while self.right:
            deep += 1
            self = self.right
        return deep
    
    def printKamus(self, deep = 0):

        print(self.data, end='')
        
        # if self.left is None:
        #     print(' '+str(deep), end='')

        if self.left:
            deep += 1
            print('-',end='')
            self.left.printKamus(deep)
            deep -= 1
            
        # if self.left:
        #     deep = self.getDeep()

        if self.right:

            print()

            # if deep != 0:
            #     print('|', end='')
            #     for i in range((deep-1)*2 +1):
            #         print(' ', end='')
            
            if deep != 0:
                for i in range(deep):
                    print('  ', end='')

            print('|')

            
            # if deep != 0:
            #     print('|', end='')
            #     for i in range((deep-1)*2 +1):
            #         print(' ', end='')

            if deep != 0:
                for i in range(deep):
                    print('  ', end='')
            
            self.right.printKamus(deep)

            
    def printKamus2(self, deep = 0, temp=[], verbose='False', reset=False, words=[]):

        

        if verbose == 'True':
            print(self.data, end='')
        if self.isLeaf():
            # print()
            # print(''.join(temp) + self.data)
            # print(temp)
            words.append(''.join(temp) + self.data)
            # print(words, 'ini temp')
            # print(words)

        if self.left:
            deep += 1
            # print('',end='')
            temp.append(self.data)
            self.left.printKamus2(deep,temp,verbose)
            deep -= 1
            temp.pop()

        if self.right:
            
            if verbose == 'True':
                print()
                print(''.join(temp), end ='')
            self.right.printKamus2(deep, temp,verbose)
        
        return words

    def printSturcture(self):
        self.printKamus()
        print()

    def print(self):
        self.printKamus2(verbose='True')
        print()
    
    def search(self, keyWord):

        print('\nMemulai pencarian \''+keyWord+'\'...\n')

        lenKeyword = len(keyWord)
        
        bebek = len(self.printKamus2())
        
        ketemu = False

        matchWord=[]

        for i in range(lenKeyword):
            
            # print(self.data)
            

            if keyWord[i] == self.data:
                # print('kiri')
                if i == lenKeyword-1 and self.isLeaf():
                    ketemu = True
                    # print(self.data)
                    # if not self.isLeaf:
                    #     ketemu = False
                elif i == lenKeyword-1:
                    ayam = self.left.printKamus2()
                    number = len(ayam)
                    # print(number, len(ayam), bebek)
                    matchWord = (ayam[-2:])
                else:
                    self = self.left

            elif ord(keyWord[i]) > ord(self.data) and self.right != None:
                # print('kanan')
                self = self.right
                while self.data != keyWord[i] and self.right != None:
                    self = self.right
                if self.data == keyWord[i]:
                    self = self.left
                    
            # print(self.data)
            # if i == lenKeyword-1:
            #     ketemu = True
            #     if not self.isLeaf:
            #         ketemu = False
            #     if self is not None:
            #         matchWord = self.printKamus2(verbose=False)
            #     # tree2word(self, matchWord, 0)
            #     # matchWord = self.tree2word()


        if ketemu:
            print('\''+keyWord + '\' ditemukan')
            # if matchWord != []:
            #     print('kata yang mungkin terkait: ')
            #     print([ keyWord + x for x in matchWord])

        else:
            print('Pencarian tidak ditemukan')
            # print([ keyWord + x for x in matchWord])
            if matchWord != []:
                print('kata yang mungkin terkait: ')
                print([ keyWord + x for x in matchWord])

    def isLeaf(self):
        return self.right is None and self.left is None

    def tree2word(self):
        words = []
        stackWord = []
        temp = Kamus(self.data)
        temp.right = self.right
        stackWord.append(self)

        while stackWord != []:
            # if stackWord[-1].data == 'r':
                # print('r here')
            # print('kata saat ini ' + stackWord[-1].data)
            if stackWord[-1].isLeaf():
                newWord = []
                for i in range(len(stackWord)):
                    newWord.append(stackWord[i].data)
                words.append(''.join(newWord))
                print(''.join(newWord))
                #TODO pop until rigth
                while stackWord[-1].isLeaf():
                    stackWord.pop()
                    print('pop')
                stackWord[-1].left = None
            elif stackWord[-1].left:
                print('kiri')
                temp = Kamus(stackWord[-1].left.data)
                temp.right = stackWord[-1].left.right
                print(temp.left)
                stackWord.append(stackWord[-1].left)
            elif stackWord[-1].right:
                print('kanan')
                stackWord.append(stackWord[-1].right)
            
            print(len(stackWord))
            if len(stackWord) == 1:
                print(stackWord[-1].left, stackWord[-1].data, stackWord[-1].right.data)
                break

        return words
        # if self.isLeaf():
        #     word.append(stackWord.join())
        # else:
        #     stackWord.append(self.data)
        #     self = self.left
            
    # def tree2word2(self):

            




        
# #     def search(self, keyWord):
        
# #         tree = self
# #         ayam = Kamus()
# #         # print(tree.data, tree.left.data)
        
# #         for char in keyWord:
            
# #             # print(tree.data)
# #             print(char + ' ' + tree.data)

# #             ayam = find(tree, char)
# #             # print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #             print (ayam)

# #             # print(char + ' ' + tree.data)
# #             #     # print('pindah' + tree.data)
# #             #     tree = tree.left
# #             # else:
# #                 # return "kata tidak diteanss"
        
# #         matchWord = []

# #         # print("data tree " + tree.data)
# #         tree2word(tree, matchWord, 0)
            
# #         return [ keyWord + x for –x in matchWord]

# # def find(tree, char):

# #     if char == tree.data:
# #         print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #         tree = tree.left
# #         print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #         print(char + " found")
# #         return tree.left
# #         # print('selesai')
# #     elif tree.right != None:
# #         # print(char + ' asli dengan pohon '+ tree.data)
# #         tree = tree.right
# #         find(tree, char)
# #         # return tree.left
# #     else:
# #         return "Kata tidak ditemukan"

def tree2word(root, path, pathLen):

    if root is None: 
        return

    if(len(path) > pathLen):  
        path[pathLen] = root.data 
    else: 
        path.append(root.data) 

    pathLen = pathLen + 1

    if root.left is None and root.right is None: 
        return 
    else: 
        tree2word(root.left, path, pathLen) 
        tree2word(root.right, path, pathLen) 


        

kamus = Kamus('buka')
kamus.add('bubar')
kamus.add('asbak')
kamus.add('cair')
kamus.add('bro')
kamus.add('bros')
kamus.add('bulat')
kamus.add('bubuk')
kamus.add('bry')
kamus.add('abu')

kamus.printSturcture()
print()
kamus.print()

kamus.search('bub')
