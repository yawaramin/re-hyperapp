type state = {.
  "nav": Component_Nav.state, "bookList": Component_BookList.state
};

let state = {
  "nav": Component_Nav.state, "bookList": Component_BookList.state
};

let actions = {
  "nav": Component_Nav.actions, "bookList": Component_BookList.actions
};

let view = [@bs] (state: state, _) => Hyperapp.(h("div", [|
  Component_Nav.view(state##nav), Component_BookList.view(state)|]));

Js.Nullable.bind(Hyperapp.getElementById("main"), [@bs] main =>
  Hyperapp.app(~state, ~actions, ~view, main))
