#! /usr/bin/env bash

GREEN='\033[0;32m'
RED='\033[0;31m'
GREY='\033[1;30m'
ENDCOLOR='\033[0m'

# Warnings
echo -e "${GREEN}Description${ENDCOLOR}"
echo -e "${GREY}This script will help to crate new local git repository, add and commit all files except .DS_Store and .o files${ENDCOLOR}"
echo -e "${GREY}It will help to add remote URL and push your files into it${ENDCOLOR}"
echo -e "${GREEN}Make sure I am in the folder with your project${ENDCOLOR}"
echo -e "Continue?: ${GREEN}y/n${ENDCOLOR}"
read answer
if [ $answer = n ]
then
    echo "all the best"
    exit 0
fi

#create .gitignote
echo ".DS_Store" > .gitignore
echo "**/*.o" >> .gitignore
echo "repo_generator.sh" >> .gitignore

# create local git, add, commit
git init
git add .
echo -e "${GREY}All your files added in local repository, except .DS_Store and *.o files${ENDCOLOR}"
echo -e "${GREEN}Write message${ENDCOLOR} for commit:"
read answer
git commit -m "$answer"

#set a new remote:
echo -e "${GREEN}Hey, give me repo URL:${ENDCOLOR}"
echo -e "${GREY}Get it from the project page${ENDCOLOR}"
read reponame
git remote add origin $reponame

# check if ssh is correct
echo -e "${GREEN}ATTENTION HERE${ENDCOLOR}"
echo "Sure your ssh key is correct in intra?"
echo -e "I can copy from id_rsa.pub. Need one?: ${GREEN}y/n${ENDCOLOR}"
read answer
if [ $answer = y ]
then
    pbcopy < ~/.ssh/id_rsa.pub
    echo "It is copied already, paste it in intra, go ahed"
    echo -e "${GREY}Your profile->settings->delete old key if needed and set new one${ENDCOLOR}"
fi

# push to remote
echo -e "Press ${GREEN}y${ENDCOLOR} when ready to push"
read answer
if [ $answer = y ]
then
    git push origin master
else
    rm -rf .git
    rm .gitignore
    echo -e "cannot help u until you say ${GREEN}y${ENDCOLOR}, I'm not that smart"
    exit 0
fi

# check for issues with repo
echo -e "Worked?: ${GREEN}y/n${ENDCOLOR}"
read answer
if [ $answer = y ]
then
    echo -e "${GREEN}good luck! :3${ENDCOLOR}"
else
    echo -e "${RED}Not empty repo?${ENDCOLOR} Want to push it with force, write: ${RED}push${ENDCOLOR} Want to pull it, write: ${GREEN}pull${ENDCOLOR}"
    read answer
    if [ $answer = push ]
    then
        git push origin master -f
        echo "hope it helped"
    elif [ $answer = pull ]
    then
        git pull origin master
        git add .
        echo -e "${GREEN}Write message${ENDCOLOR} for commit:"
        read answer
        git commit -m "$answer"
        git push origin master
    else
        echo "cannot help u, I'm not that smart"
        exit 0
    fi
fi
