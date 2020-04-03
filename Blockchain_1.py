import hashlib

import json

#reward for mining block , either  you can fix the value or  take a % of the transaction  it depends
reward = "Scooby snack"

#Gensis block initialization
genesis_block = {

   'previous_hash': '',

   'index': 0,

   'transaction': [],

   'nonce': 2018
   #It is used in mining process

}
#Declaring Gensis Block
blockchain = [genesis_block]

open_transactions = []

owner = 'kaka'

def valid_proof(transactions, last_hash, nonce):

   guess = (str(transactions) + str(last_hash) + str(nonce)).encode()

   guess_hash = hashlib.sha256(guess).hexdigest()
    #generating a Hashcode for a particular verified Transaction
   last_chars = guess_hash[-10:]
   #We have reduced the print to last 10 characters of each verification
   print(last_chars)
   #if first two characters is equal to 00 , it means it belongs to this specific blockchain
   return guess_hash[0:2] == '2018'


def pow():

   last_block = blockchain[-1]

   last_hash = hash_block(last_block)

   nonce = 0

   while not valid_proof(open_transactions, last_hash, nonce):
       #value of nonce is incremented when the transaction is verified 
       nonce += 1

   return nonce


def hash_block(block):

   return hashlib.sha256(json.dumps(block).encode()).hexdigest()
    #1.sha 256-> SHA-256 is a one-way function that converts a text of any length into a string of 256 bits.
    #2.encode()-> Used to encode the string into hexidigest format
    #3.hexidigest()-> string is returned as a string of double length , containg only hexadecimal digits.
 
def get_last_value():

   """ extracting the last element of the blockchain list """

   return(blockchain[-1])

def mine_block():

   last_block = blockchain[-1]

   hashed_block = hash_block(last_block)
    #we compare the value of hash of the last block and value of hash stored in the present block of the last block , 
    # if they are not same that means blockchain has been modified 
   nonce = pow()
    #To proof of work to check for transaction verification 

   reward_transaction = {

           'sender': 'MINING',

           'recipient': owner,

           'amount': reward

       }
    #Adding the mining transaction 
   open_transactions.append(reward_transaction)

   block = {

       'previous_hash': hashed_block,

       'index': len(blockchain),

       'transaction': open_transactions,

       'nonce': nonce

   }

   blockchain.append(block)


def add_value(recipient, sender, amount=1.0):

   transaction = {'sender': sender,

   'recipient': recipient,

   'amount': amount}

   open_transactions.append(transaction)

def get_transaction_value():

   tx_sender=input('Enter the sender of the transaction:')
   
   tx_recipient = input('Enter the recipient of the transaction: ')

   tx_amount = float(input('Enter your transaction amount '))

   return tx_sender,tx_recipient, tx_amount



def get_user_choice():

   user_input = int(input("Please give your choice here: "))

   return user_input

def print_block():

   for block in blockchain:

       print("Here is your block")

       print(block)

print("Genesis Block : {}".format(blockchain))

while True:

   print("Choose an option")

   print('Choose 1 for adding a new transaction')

   print('Choose 2 for mining a new block')

   print('Choose 3 for printing the blockchain')

   print('Choose anything else if you want to quit')

   user_choice = get_user_choice()

   

   if user_choice == 1:

       tx_data = get_transaction_value()

       sender,recipient, amount = tx_data

       add_value(recipient,sender, amount=amount)

       print(open_transactions)
       #open_transactions is a list of all the transactions that have happened and mined 


   elif user_choice == 2:

       mine_block()


   elif user_choice == 3:

       print_block()

   
   else:

       break