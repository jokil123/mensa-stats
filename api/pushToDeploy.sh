set -e

git checkout deploy
git pull
git merge master
git push
git checkout master
git branch