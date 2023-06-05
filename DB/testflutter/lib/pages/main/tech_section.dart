import 'package:duration/duration.dart';
import 'package:flutter/material.dart';
import 'package:testflutter/pages/main/model/changeable_substance.dart';
import 'package:testflutter/pages/main/model/changeable_tech.dart';
import 'package:testflutter/pages/main/model/substance.dart';
import 'package:testflutter/pages/main/model/tech_comp_rel.dart';
import 'package:testflutter/pages/main/model/tech_with_sub.dart';
import 'package:testflutter/pages/main/utils_queries.dart';

Widget getTechSection(
    void Function(void Function()) setState, BuildContext Function() context) {
  _setState = setState;
  _context = context;
  return Column(children: [
    _getSearchBar(_subs),
    Expanded(
        child: Row(
      children: [
        Expanded(child: _searchTechsColumn(_subs)),
        Expanded(child: _techInfoColumn())
      ],
    ))
  ]);
}

late void Function(void Function()) _setState;
late BuildContext Function() _context;
final List<Substance> _subs = [];
final List<TechCompRel> _curRels = [];
TechWithSub _selectedTechWithSub =
    TechWithSub(-1, -1, "", "", Duration.zero, -1);
late ChangeableTech _editableTech;

Widget _getSearchBar(List<Substance> subs) {
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

Column _searchTechsColumn(List<Substance> subs) {
  return Column(children: [
    Expanded(
        child: ListView.builder(
            itemCount: subs.length,
            itemBuilder: (BuildContext b, int index) {
              return ListTile(
                  title: Text(subs[index].name),
                  onTap: () async {
                    _selectedTechWithSub = await searchTech(subs[index].name);
                    await searchTechCompRel(_curRels, _selectedTechWithSub.id);
                    _editableTech =
                        ChangeableTech.fromTech(_selectedTechWithSub);
                    _setState(() {});
                  });
            })),
    Container(
      color: Colors.amber,
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceAround,
        children: [
          IconButton(
              onPressed: () => _createAddTechDialog(_context()),
              icon: const Icon(
                Icons.add,
                color: Colors.black,
              )),
          IconButton(
              onPressed: () => removeTech(_selectedTechWithSub),
              icon: const Icon(
                Icons.remove,
                color: Colors.black,
              ))
        ],
      ),
    )
  ]);
}

late ChangeableTech _techToAdd;

void _createAddTechDialog(BuildContext context) {
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        List<TechCompRel> selectedRels = [];
        final List<Substance> subs = [];
        final List<int> count = [1];
        final tc = TextEditingController();
        _techToAdd = ChangeableTech();

        return StatefulBuilder(builder: (context, setState) {
          return AlertDialog(
            title: const Text("Добавить новую технологию"),
            content: Row(
              children: [
                SizedBox(width: 250, child: _columnWithDesc(tc)),
                SizedBox(
                    width: 500,
                    child: _columnWithRels(selectedRels, subs, count, setState))
              ],
            ),
            actions: [
              TextButton(
                  onPressed: () => Navigator.of(context).pop(),
                  child: const Text("Отмена")),
              TextButton(
                  onPressed: () {
                    _techToAdd.creationTime =
                        parseDuration(tc.text, separator: ' ');
                    addTech(_techToAdd, selectedRels);
                    Navigator.of(context).pop();
                  },
                  child: const Text("Создать"))
            ],
            actionsAlignment: MainAxisAlignment.spaceAround,
          );
        });
      });
}

Row _columnWithRels(
    final List<TechCompRel> selectedRels,
    final List<Substance> subs,
    final List<int> count,
    void Function(void Function()) f) {
  return Row(children: [
    Expanded(child: _columnWithSelectedRels(selectedRels, f)),
    Expanded(child: _columnWithSubsSelection(count, subs, selectedRels, f))
  ]);
}

Column _columnWithSelectedRels(
    List<TechCompRel> selectedRels, void Function(void Function()) f) {
  return Column(children: [
    Expanded(
        child: Container(
      color: Colors.amberAccent,
      child: ListView.builder(
        itemCount: selectedRels.length,
        itemBuilder: (BuildContext context, int index) {
          return ListTile(
            title: Text(
                "${selectedRels[index].name}, ${selectedRels[index].count} шт."),
            onTap: () {
              f(() => selectedRels.removeAt(index));
            },
          );
        },
      ),
    )),
  ]);
}

Column _columnWithSubsSelection(List<int> count, List<Substance> subs,
    List<TechCompRel> selectedRels, void Function(void Function()) f) {
  return Column(children: [
    Row(
      children: [
        Expanded(
            child: TextField(
                decoration:
                    const InputDecoration(hintText: "Введите лекарство..."),
                onChanged: (name) => f(() {
                      searchSubstances(name, subs);
                    }))),
        const Icon(Icons.search, color: Colors.white)
      ],
    ),
    Row(
      children: [
        Expanded(
            child: TextField(
                decoration:
                    const InputDecoration(hintText: "Введите количество..."),
                onChanged: (name) {
                  count[0] = int.parse(name);
                })),
        const Icon(Icons.add_circle_outline, color: Colors.white)
      ],
    ),
    Expanded(
        child: ListView.builder(
            itemCount: subs.length,
            itemBuilder: (BuildContext b, int index) {
              return ListTile(
                  title: Text(subs[index].name),
                  onTap: () {
                    f(() {
                      selectedRels.add(TechCompRel(
                          subs[index].id, subs[index].name, count[0]));
                    });
                  });
            }))
  ]);
}

Column _columnWithDesc(TextEditingController tc) {
  return Column(children: [
    Expanded(
        child: TextField(
      decoration: const InputDecoration(hintText: "Введите название лекарства"),
      onChanged: (str) => _techToAdd.medicineName = str,
    )),
    Expanded(
        child: TextField(
      decoration: const InputDecoration(hintText: "Введите описание"),
      onChanged: (str) => _techToAdd.description = str,
    )),
    Expanded(
        child: TextField(
      decoration: const InputDecoration(
          hintText: "Введите время производства (1w 1d 1h 1m 1s 1ms 1us)"),
      controller: tc,
    )),
    Expanded(
        child: TextField(
      expands: false,
      decoration:
          const InputDecoration(hintText: "Введите производимое количество"),
      onChanged: (str) => _techToAdd.medCount = int.parse(str),
    )),
  ]);
}

Column _techInfoColumn() {
  TextEditingController dscController = TextEditingController.fromValue(
    TextEditingValue(
      text: _selectedTechWithSub.description,
    ),
  );
  TextEditingController timeController = TextEditingController.fromValue(
    TextEditingValue(
      text: _selectedTechWithSub.creationTime.toString(),
    ),
  );
  return Column(
    children: [
      Expanded(
          child: Container(
              color: Colors.amberAccent,
              child: ListView(
                children: [
                  ListTile(
                      title: TextField(
                          enabled: true,
                          decoration: InputDecoration(
                              hintText: _selectedTechWithSub.medicineName),
                          onChanged: (val) => _editableTech.medicineName = val),
                      subtitle: const Text("Название лекарства")),
                  ListTile(
                      title: TextField(
                        enabled: true,
                        keyboardType: TextInputType.multiline,
                        maxLines: null,
                        decoration: InputDecoration(
                            hintText: _selectedTechWithSub.description,
                            border: InputBorder.none),
                        controller: dscController,
                      ),
                      subtitle: const Text("Описание")),
                  ListTile(
                      title: TextField(
                        enabled: true,
                        keyboardType: TextInputType.text,
                        maxLines: 1,
                        decoration: InputDecoration(
                            hintText:
                                _selectedTechWithSub.creationTime.toString(),
                            border: InputBorder.none),
                        controller: timeController,
                      ),
                      subtitle: const Text("Время производства")),
                  ListTile(
                      title: TextField(
                          enabled: true,
                          decoration: InputDecoration(
                              hintText:
                                  _selectedTechWithSub.medCount.toString()),
                          onChanged: (val) =>
                              _editableTech.medCount = int.parse(val)),
                      subtitle: const Text("Производимое кол-во лекарства")),
                  ListTile(
                    title: IconButton(
                        onPressed: () async {
                          _editableTech.creationTime = parseTime(timeController.text);
                          _editableTech.description = dscController.text;
                          await saveTechChanges(_editableTech);
                          _setState(() => {});
                        },
                        icon: const Icon(Icons.save)),
                    subtitle: const Center(child: Text("Сохранить изменения")),
                  )
                ],
              ))),
      Container(
        color: Colors.amber,
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            IconButton(
                onPressed: () async{
                  _sRels.clear();
                  await searchTechCompRel(_sRels, _selectedTechWithSub.id);
                  _editTechRelsDialog(_context());
                },
                icon: const Icon(Icons.edit))
          ],
        ),
      )
    ],
  );
}

List<TechCompRel> _sRels = [];
void _editTechRelsDialog(BuildContext context){
  showDialog(
      context: context,
      builder: (BuildContext ctx) {
        final List<Substance> subs = [];
        final List<int> count = [1];

        return StatefulBuilder(builder: (context, setState) {
          return AlertDialog(
            title: const Text("Изменить технологию"),
            content: Row(
              children: [
                SizedBox(
                    width: 500,
                    child: _columnWithRels(_sRels, subs, count, setState))
              ],
            ),
            actions: [
              TextButton(
                  onPressed: () => Navigator.of(context).pop(),
                  child: const Text("Отмена")),
              TextButton(
                  onPressed: () {
                    saveRelTechChanges(_selectedTechWithSub.id, _sRels);
                    Navigator.of(context).pop();
                  },
                  child: const Text("Сохранить"))
            ],
            actionsAlignment: MainAxisAlignment.spaceAround,
          );
        });
      });
}