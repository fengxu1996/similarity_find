# -*- coding: utf-8 -*-
# !/usr/bin/env python

import sys
import os
import jieba

# 保存至文件
def savefile(savepath, content):
    fp = open(savepath, "wb")
    fp.write(content)
    fp.close()


# 读取文件
def readfile(path):
    fp = open(path, "rb")
    content = fp.read()
    fp.close()
    return content


# 创建停用词列表
def builtStopList(StopWordFilePath):
    StopWords = list()
    with open(StopWordFilePath, "rb") as f:
        for line in f.readlines():
            StopWords.append(line.strip())
    return StopWords


corpus_path = "train_corpus_small/"  # 未分词分类语料库路径
seg_path = "train_corpus_seg/"  # 分词后分类语料库路径
stopwordspath = "停用词\stopword.txt"  # 停用词表路径
StopWordsList = builtStopList(stopwordspath)

catelist = os.listdir(corpus_path)  # 获取corpus_path下的所有子目录

# 获取每个目录下所有的文件
for mydir in catelist:
    class_path = corpus_path + mydir + "/"  # 拼出分类子目录的路径
    seg_dir = seg_path + mydir + "/"  # 拼出分词后语料分类目录
    if not os.path.exists(seg_dir):  # 是否存在目录，如果没有创建
        os.makedirs(seg_dir)
    file_list = os.listdir(class_path)  # 获取class_path下的所有文件
    for file_path in file_list:  # 遍历类别目录下文件
        fullname = class_path + file_path  # 拼出文件名全路径
        content = readfile(fullname).strip()  # 读取文件内容
        content = content.replace("\r\n".encode("utf-8"), "".encode("utf-8"))  # 删除换行和多余的空格
        content_seg = jieba.cut(content.strip())  # 为文件内容分词
        content_seg_List = list()
        for i in content_seg:
            if i.strip().encode("utf-8") not in StopWordsList:
                if i.strip().encode("utf-8") != "".encode("utf-8") and i.strip().encode("utf-8") != " ".encode("utf-8"):
                    content_seg_List.append(i.strip())
            pass
        savefile(seg_dir + file_path, " ".join(content_seg_List).encode("utf-8"))  # 将处理后的文件保存到分词后语料目录
        # savefile(seg_dir + file_path, content)

print(u"中文语料分词结束！！！")
print(u"去除停用词结束")
