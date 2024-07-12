def date_query_params(datetime_from: str | None = None, datetime_to: str | None = None):
    return {'from': datetime_from, 'to': datetime_to}


def order_query_params(column: str = 'id', order: str = 'descending'):
    return {'col': column, 'order': order}
