rmdir /s /q .history
git add .
set commit_message=Commit on %date%
set commit_message="头文件重构"
git commit -m "%commit_message%"
git push