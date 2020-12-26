#!/bin/bash

sshfs -o StrictHostKeyChecking=no storage@10.2.3.91:/home/storage/dirprueba ./dirprueba
./fmmain_server