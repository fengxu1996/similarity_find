# -*- coding: utf-8 -*-
# !/usr/bin/env python

"""
将k_shingling后的词统一用数字表示
"""
import os
import shutil


def make_path(p):
    if os.path.exists(p):  # 判断文件夹是否存在
        shutil.rmtree(p)  # 删除文件夹
    os.mkdir(p)  # 创建文件夹

crash = 0
shingling_path = "train_corpus_shingling/"  # shingling后文件保存路径
catelist = os.listdir(shingling_path)  # 分类子目录
SET = set()
DICT = dict()
for mydir in catelist:
    dirPath = shingling_path + mydir + "/"
    dirlist = os.listdir(dirPath)
    for docName in dirlist:
        docPath = dirPath + docName
        sequences = None
        with open(docPath, "rb") as f:
            sequences = f.read()
        sequenceslist = sequences.decode("utf-8").split(" ")
        for i in sequenceslist:
            if i not in SET:
                SET.add(i.strip())
            else:
                crash = crash+1
        pass

print("域大小为", len(SET))
print("用集合统计域大小时发生碰撞次数", crash)
cnt = 1
for i in SET:
    DICT[i] = cnt
    cnt = cnt + 1
del SET

doAfterPath = "train_corpus_convertToNum/"  # 转变为序号后文件保存路径

for mydir in catelist:
    dirPath = shingling_path + mydir + "/"  # 输入文件子目录路径
    doAfterDirPath = doAfterPath + mydir + "/"  # 转化为序号后的文件子目录路径
    make_path(doAfterDirPath)  # 创建子目录文件
    dirlist = os.listdir(dirPath)
    for docName in dirlist:
        docPath = dirPath + docName  # 完整的文件输入路径
        doAfterDocPath = doAfterDirPath + docName  # 完整的文件输出路径
        sequences = None
        with open(docPath, "rb") as f:
            sequences = f.read()
        sequenceslist = sequences.decode("utf-8").split(" ")
        contentConvertTo = ""  # 保存转换为序号后的内容
        isfirst = True
        for i in sequenceslist:
            if isfirst == True:
                contentConvertTo = contentConvertTo + str(DICT[i])
                isfirst = False
            else:
                contentConvertTo = contentConvertTo + " " + str(DICT[i])
        with open(doAfterDocPath, "wb+") as f:
            f.write(contentConvertTo.encode("utf-8"))
print("转换完成!!!")
