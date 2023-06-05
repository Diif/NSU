class Order{
  final int id;
  final int stage;
  final int clientId;
  final DateTime? readyTime;
  final DateTime? receiveTime;
  final DateTime orderTime;

  const Order(this.id, this.stage, this.clientId, this.readyTime, this.receiveTime, this.orderTime);

}