class MyObj {

};

class MyObjBuilder {
public:
  void makeObject() {}

};

template <typename BuiltType, typename Builder>
void makeAndProcessObject (const Builder& builder)
{
    BuiltType val = builder.makeObject();
    // do stuff with val
}

int main() {
  MyObjBuilder builder;
  makeAndProcessObject<MyObj>( builder );
}
