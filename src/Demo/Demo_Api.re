let random100() = Js.Math.random_int(1, 100);

let addYear(date) = {
  open Js.Date;
  date |> getFullYear |> (+.)(1.) |> setFullYear(date) |> ignore;
  date
};

let addMonth(date) = {
  open Js.Date;
  let month = getMonth(date);

  if (month == 12.) {
    date |> addYear |> ignore;
    1. |> setMonth(date) |> ignore;
  } else date |> getMonth |> (+.)(1.) |> setMonth(date) |> ignore;

  date
};

let books(query) = Js.Promise.resolve([|
  { "id": random100(),
    "title": query,
    "description": "Hello, World!",
    "author": "JRR Tolkien",
    "copies": 2,
    "available": 1,
    "status": `borrowed(Js.Date.makeWithYMD(
      ~year=2018.0, ~month=2.0, ~date=28.0, ())) },

  { "id": random100(),
    "title": query,
    "description": "Goodbye, Cruel World!",
    "author": "Rudyard Kipling",
    "copies": 2,
    "available": 0,
    "status": `quo }
|]);

let hold(_bookId) = Js.Promise.resolve(Js.Date.make());
let return(_bookId) = Js.Promise.resolve();
let cancelHold(_bookId) = Js.Promise.resolve();

let borrow(_bookId) = ()
|> Js.Date.make |> addMonth |> Js.Promise.resolve;
