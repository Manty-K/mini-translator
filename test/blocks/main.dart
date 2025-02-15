import 'dart:io';

List<int> indentArr = [];

int indentDepth = 0;

void blockOpen() {
  if (indentArr.length <= indentDepth) {
    indentArr.add(1);
  }

  indentDepth++;

  printIndent();
}

void blockClose() {
  indentDepth--;

  indentArr[indentDepth] += 1;

  while (indentArr.length > indentDepth + 1) {
    indentArr.removeLast();
  }
}

void printIndent() {
  print(indentArr.join('.'));
}

void main() async {
  File file = File('input.txt');

  if (!await file.exists()) {
    print('File does not exist');
    return;
  }

  String data = await file.readAsString();

  for (var character in data.split('')) {
    if (character == '{') {
      blockOpen();
    }
    if (character == '}') {
      blockClose();
    }
  }
}
