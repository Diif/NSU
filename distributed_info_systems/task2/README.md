При первом запуске необходимо через mongosh подключиться к БД и инициализировать кластер:

rs.initiate( {
   _id : "rs",
   members: [
      { _id: 0, host: "node0.mongo:27017" },
      { _id: 1, host: "node1.mongo:27017" },
      { _id: 2, host: "node2.mongo:27017" }
   ]
})