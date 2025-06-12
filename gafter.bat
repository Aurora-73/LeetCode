rmdir /s /q .history
git add .
set commit_message=Commit on %date%
@REM git commit -m "%commit_message%"
git commit -m "修改任务配置，使用动态链接库"
git push