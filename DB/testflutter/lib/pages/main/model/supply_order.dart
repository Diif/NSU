class SupplyOrder{
  final int id;
  final DateTime time;
  final int subId;
  final String subName;
  final int countToReceive;
  final int receivedCount;

  SupplyOrder(this.id, this.time, this.subId, this.countToReceive, this.receivedCount, this.subName);

}