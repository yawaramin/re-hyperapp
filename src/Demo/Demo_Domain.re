type bookId = string;

type book = {
  author: string,
  available: int,
  copies: int,
  description: string,
  id: bookId,
  title: string,
  status: [`held | `borrowed(Js.Date.t) | `quo],
};
