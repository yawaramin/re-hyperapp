module Domain = Demo_Domain;

type state = {.
  books: list(Domain.book),
  activeBookId: option(Domain.bookId),
};

type actions = {.};
type props = unit;

let state = {"books": [], "activeBookId": None};
let actions = Js.Obj.empty();

let make(~state, ~actions, ~props=(), _) = {
  ignore(state);
  ignore(actions);
  ignore(props);
  <span> </span>;
};
