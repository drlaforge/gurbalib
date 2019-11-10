string make_list(string *items)
{
string result;
int i, size;
result = "";
size = sizeof(items);
if (size == 1)
{
result = result+items[0];
}
else if(size == 2) {
result = result+items[0]+" and "+items[1];
}
else {
for(i = 0; i < size-2; i++)
{
result = result+items[i]+", ";
}
result = result+items[size-2]+" and "+items[size-1];
}
return result;
}
