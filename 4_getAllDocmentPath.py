# -*- coding: utf-8 -*-
# !/usr/bin/env python

import os

SAVELIST = list()  # 保存所有文件路径名

path = "train_corpus_convertToNum/"

catelist = os.listdir(path)

for mydir in catelist:
    pathi = path + mydir + "/"
    docPathList = os.listdir(pathi)
    for docName in docPathList:
        x = pathi + docName
        SAVELIST.append(x)


with open("filePath/filePath.txt", "wb+") as f:
    for i in SAVELIST:
        f.write((i+"\n").encode("utf-8"))

for i in SAVELIST:
    print(i)