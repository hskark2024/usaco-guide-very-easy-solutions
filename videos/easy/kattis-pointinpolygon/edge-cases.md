# Edge-case checklist

- Query strictly inside or outside.
- Query on a horizontal, vertical, or slanted edge.
- Query exactly at a polygon vertex.
- Ray passing through a vertex.
- Horizontal edges that must not count as crossings.
- Concave polygons and points inside indentations.
- Clockwise and counterclockwise vertex order.
- Negative and large coordinates.
- Multiple polygons followed by the zero sentinel.
