type state = {.
  "nav": {. "query": string},
  "bookList": {. "value": option(Component_BookList.books)}
};

let state = {"nav": {query: ""}, "bookList": {value: None}};

let actions = {
  "nav": Component_Nav.actions, "bookList": Component_BookList.actions
};

let view = [@bs] (state: state, _) => Hyperapp.(h("div", [|
  Component_Nav.view(state##nav), Component_BookList.view(state)|]));

Js.Nullable.bind(Hyperapp.getElementById("main"), [@bs] main =>
  Hyperapp.app(~state, ~actions, ~view, main))
