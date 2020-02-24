##How to start DB

###Docker Way
####Install Mongo DB
install docker: see https://docs.docker.com/docker-for-windows/install/
docker pull couchdb:
####Start Couch DB
docker run -p 5984:5984 --name dayzdb couchdb
docker start dayzdb

###Native Way
####Install

####Start