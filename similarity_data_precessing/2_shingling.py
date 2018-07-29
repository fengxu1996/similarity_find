# -*- coding: utf-8 -*-
# !/usr/bin/env python
import os
import shutil

def make_path(p):
    if os.path.exists(p):  # 判断文件夹是否存在
        shutil.rmtree(p)  # 删除文件夹
    os.mkdir(p)  # 创建文件夹


def ShinglingContent(contentSplit, K):
    if len(contentSplit) < K:  # 如果词数不足K则直接把一个文档压缩成一个词
        return "".join(contentSplit)
    shinglingset = set()  # shingling后的词去重
    for i in range(len(contentSplit) - K + 1):
        s = ""
        for ii in range(K):
            s = s + contentSplit[ii+i]
        shinglingset.add(s)
        pass
    shinglinglist = list(shinglingset)
    return shinglinglist
    pass


SETALL = set()

K_of_shingling = 5  # 设置shingling K的大小

seg_path = "train_corpus_seg/"  # 分词,去停用词后分类语料库路径
shingling_path = "train_corpus_shingling/"  # shingling后文件保存路径
catelist = os.listdir(seg_path)

for mydir in catelist:
    InputDir_path = seg_path + mydir + "/"  # 分类子目录的路径
    InputDir_path_list = os.listdir(InputDir_path)  # 分类子目录下的文件名列表
    OutputDir_path = shingling_path + mydir + "/"  # k_shingling 后分类子目录路径

    make_path(OutputDir_path)  # 创建输出目录

    for docName in InputDir_path_list:
        FullInputPath = InputDir_path + docName  # 完整文件输入路径
        content = ""  # 保存shingling前文件内容

        shinglingContentList = list()  # 保存k_shingling后的列表
        # shinglingContent = ""  # 保存shingling后文件内容

        # 读取分词，去停用词后的文件内容
        with open(FullInputPath, "rb") as f:
            for line in f.readlines():
                content = content + line.decode("utf-8")
            pass
        spaceSplitContent = content.split(" ")
        shinglingContentList = ShinglingContent(spaceSplitContent, K_of_shingling)  # shingling后列表
        # 测试输出
        # print(shinglingContentList)
        FullOutputPath = OutputDir_path + docName  # 完整文件输出路径
        # K_shingling后输出到文件
        with open(FullOutputPath, "wb+") as f:
            f.write(" ".join(shinglingContentList).encode("utf-8"))
