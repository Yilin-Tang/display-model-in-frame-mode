# display-model-in-frame-mode
This code uses OpenGL and Assimp to display obj model in frame mode.

## Discription
This code can display obj model with triangulated mesh by OpenGL and Assimp in C++. It only requires the obj file have vertex coordinate and faces indices. I run it in Visual Studio 2019 and the required libraries are installed by vcpkg. I am not sure whether it can successfully run in other environments or conditions.

## Usage
### Required Libraries
The following libraries are required:
- GLFW
- glad
- GLM  --a math library designed for OpenGL
- Assimp  --used to read and process obj file

### Change Property
#### change obj file
Replace your obj file in ``main.cpp``
```
    Mesh mesh("bunny.obj");  // change it to your file path
```

#### modify vertex shader
The presented vertex shader ``vertex_shader_for_bunny.txt`` is specially for ``bunny.obj`` to move it to the center and enlarge it to be clear. If you change the obj file, remember to change the vertex shader too.

Vertex shader and fragment shader can be changed in ``main.cpp``
```
    Shader shader("vertex_shader_for_bunny.txt", "fragment_shader.txt");
```

#### others
- window's size
change ``SCR_width`` and ``SCR_height`` in ``main.cpp``
```
const unsigned int SCR_width = 1000;
const unsigned int SCR_height = 1000;
```

- color:
change background color in ``Mesh_assimp.cpp``
```
void Mesh::draw(GLFWwindow* window, Shader& shader)
...
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // background color
```

change frame color in ``fragment_shader.txt``
```
FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
```

## Reference
This code refers to the [chinese translation](https://learnopengl-cn.github.io/) of https://learnopengl.com/.