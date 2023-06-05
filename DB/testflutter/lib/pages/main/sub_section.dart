import 'package:flutter/material.dart';
import 'package:testflutter/pages/main/model/changeable_substance.dart';
import 'package:testflutter/pages/main/model/substance.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

Widget getSubSection(void Function(void Function()) setState, BuildContext Function() context) {
  _setState = setState;
  _context = context;
  return Column(children: [
    _getSearchBar(_subs),
    Expanded(child: Row(
      children: [
        Expanded(child: _searchSubstancesColumn(_subs)),
        Expanded(child: _subInfoColumn())
      ],
    ))
  ]);
}

late void Function(void Function()) _setState;
late BuildContext Function() _context;
final List<Substance> _subs = [];
final Map<int, String> _categories = {};
Substance _selectedSub = const Substance(-1, "", -1, -1, -1, "-1");
late ChangeableSubstance _editableSub;

Widget _getSearchBar(List<Substance> subs){
  return Row(
    children: [
      Expanded(
          child: TextField(
              decoration:
              const InputDecoration(hintText: "Введите лекарство..."),
              onChanged: (name) => _setState(() {
                searchSubstances(name, subs);
              }))),
      const Icon(Icons.search, color: Colors.white)
    ],
  );
}

Column _searchSubstancesColumn(List<Substance> subs) {
  return Column(children: [
    Expanded(
        child: ListView.builder(
            itemCount: subs.length,
            itemBuilder: (BuildContext b, int index) {
              return ListTile(
                  title: Text(subs[index].name),
                  onTap: () {
                    _setState(() {
                      _selectedSub = subs[index];
                      _editableSub = ChangeableSubstance.fromSub(_selectedSub, _categories[_selectedSub.categoryId] as String);
                    });
                  });
            })),
    Container(
      color: Colors.amber,
      child: Row(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          IconButton(
              onPressed: () => _createAddSubDialog(_context()),
              icon: const Icon(
                Icons.add,
                color: Colors.black,
              ))
        ],
      ),
    )
  ]);
}

late ChangeableSubstance _subToAdd;

void _createAddSubDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        _subToAdd = ChangeableSubstance();
        return AlertDialog(
          title: const Text("Добавить новое лекарство"),
          content: Column(children: [
            Expanded(
                child: TextField(
                  decoration: const InputDecoration(hintText: "Введите название"),
                  onChanged: (str) => _subToAdd.name = str,
                )),
            Expanded(
                child: TextField(
                  decoration: const InputDecoration(hintText: "Введите категорию"),
                  onChanged: (str) => _subToAdd.categoryName = str,
                )),
            Expanded(
                child: TextField(
                  decoration: const InputDecoration(hintText: "Введите критическое количество"),
                  onChanged: (str) => _subToAdd.critCount = int.parse(str),
                )),
            Expanded(
                child: TextField(
                  expands: false,
                  decoration:
                  const InputDecoration(hintText: "Введите цену"),
                  onChanged: (str) => _subToAdd.pricePcs = str,
                )),
          ]),
          actions: [
            TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text("Отмена")),
            TextButton(
                onPressed: () {
                  addSub(_subToAdd);
                  Navigator.of(context).pop();
                },
                child: const Text("Создать"))
          ],
          actionsAlignment: MainAxisAlignment.spaceAround,
        );
      });
}


Column _subInfoColumn() {
  if (_categories.isEmpty) {
    searchCategories(_categories);
  }
  return Column(
    children: [
      Expanded(
          child: Container(color: Colors.amberAccent,child:
          ListView(
            children: [
              ListTile(
                  title: TextField(
                      enabled: true,
                      decoration: InputDecoration(hintText: _selectedSub.name),
                    onChanged: (val) => _editableSub.name = val),
                  subtitle: const Text("Название")),
              ListTile(
                  title: TextField(
                      enabled: true,
                      decoration: InputDecoration(
                          hintText: _categories[_selectedSub.categoryId]),
                    onChanged: (val) => _editableSub.categoryName = val),
                  subtitle: const Text("Категория")),
              ListTile(
                  title: TextField(
                      enabled: false,
                      decoration:
                      InputDecoration(hintText: _selectedSub.count.toString())),
                  subtitle: const Text("Количество на складе")),
              ListTile(
                  title: TextField(
                      enabled: true,
                      decoration: InputDecoration(
                          hintText: _selectedSub.critCount.toString()),
                    onChanged: (val) => _editableSub.critCount = int.parse(val)),
                  subtitle: const Text("Критическое количество")),
              ListTile(
                  title: TextField(
                    enabled: true,
                    decoration:
                    InputDecoration(hintText: _selectedSub.pricePcs.toString()),
                    onChanged: (val) => _editableSub.pricePcs = val,
                  ),
                  subtitle: const Text("Цена за штуку"))
            ],
          ))),
      Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            IconButton(onPressed: () async{
              await saveSubChanges(_editableSub);
              _setState(() => {});
            }, icon: const Icon(Icons.save))
          ],
        ),
      )
    ],
  );
}
