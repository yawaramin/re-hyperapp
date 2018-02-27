[@bs.deriving jsConverter] type t = [
| `held
| `borrowed(Js.Date.t)
| `quo
];
