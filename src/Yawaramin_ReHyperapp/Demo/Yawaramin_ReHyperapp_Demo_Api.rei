/**/

/** [books query] returns a set of books that match the [query] criteria.
    The returned books are in a format specialised for the user. */
let books:
  string =>
  Js.Promise.t(array({.
    "author": string,
    "available": int,
    "copies": int,
    "description": string,
    "id": int,
    "title": string,
    "status": Yawaramin_ReHyperapp_Demo_Domain_Status.t
  }));

let hold: int => Js.Promise.t(Js.Date.t);
let return: int => Js.Promise.t(unit);
let cancelHold: int => Js.Promise.t(unit);
let borrow: int => Js.Promise.t(Js.Date.t);
