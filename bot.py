#!/usr/bin/python3

import discord
import subprocess
import glob
import shlex

EXIT_SUCCESS = 0

# Retrieve the discord bot token
tokenFile = open("token.txt", 'r')
token = tokenFile.readline()

client = discord.Client()

async def run_program(cmd, messageObject):

    # Run the command
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    if process.returncode == EXIT_SUCCESS:
        output = stdout
    else:
        output = stderr

    # Send output to the message Object's channel
    await messageObject.channel.send((output.decode("utf-8").strip("./")))
        

@client.event
async def on_ready():
    print("{} has connected to Discord".format(client.user))

@client.event
async def on_message(message):

    # Don't trigger on bot's sent messages
    if message.author != client.user:

        if message.channel.type == discord.ChannelType.private:
            print("Private message received")
            
            # Create a unix-like arguments list
            args = ["./enigma.out"] + shlex.split(message.content)
            
            await run_program(args, message)

        else:
        
            if message.content.startswith("!enigma "):

                print("Command received")
            
                # Create a unix-like arguments list (ignoring the command prefix)
                args = ["./enigma.out"] + shlex.split(message.content)[1:]
               
                await run_program(args, message)

client.run(token)