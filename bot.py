#!/usr/bin/python3

import discord
import subprocess
import glob
import shlex

tokenFile = open("token.txt", 'r')
token = tokenFile.readline()

client = discord.Client()

@client.event
async def on_ready():
    print("{} has connected to Discord".format(client.user))

@client.event
async def on_message(message):
    if message.author != client.user:

        if message.channel.type == discord.ChannelType.private:
            print("Private message received")
            args = ["./enigma.out"] + shlex.split(message.content)
            output = subprocess.check_output(args) #glob.glob("./" + "enigma.*")[0], message.content)
            await message.channel.send((output.decode("utf-8").strip("./")))
        else:
            print("Public message receieved")

client.run(token)