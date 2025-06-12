@echo off
chcp 65001 >nul
rmdir /s /q .history
git add .
set commit_message=Commit on %date%
git commit -m "%commit_message%"
git push