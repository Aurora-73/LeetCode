@echo off
rmdir /s /q .history
git add .
set commit_message=Commit on %date%
set commit_message="构造树的空节点改为宏EMPTY_NODE"
git commit -m "%commit_message%"
git push