#!/usr/bin/python3

import discord
import subprocess
import glob
import shlex

# Retrieve the discord bot token
tokenFile = open("token.txt", 'r')
token = tokenFile.readline()

client = discord.Client()

@client.event
async def on_ready():
    print("{} has connected to Discord".format(client.user))

@client.event
async def on_message(message):

    # Don't trigger on bot's sent messages
    if message.author != client.user:

        if message.channel.type == discord.ChannelType.private:
            print("Private message received")
            
            # Create a unix-like arguments list using shlex
            args = ["./enigma.out"] + shlex.split(message.content)
            
            # Run engima executable with arguments
            output = subprocess.check_output(args) #glob.glob("./" + "enigma.*")[0], message.content)

            # Send executable output to the channel the message was received from
            await message.channel.send((output.decode("utf-8").strip("./")))

        else:
            if message.content.startswith("!"):
                print("Command received")

client.run(token)