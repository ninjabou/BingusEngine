#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33

#include "GraphicsManager.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include "sokol_gfx.h"
#include <iostream>

namespace bingusengine {
    namespace {
        struct Uniforms {
            mat4 projection;
            mat4 transform;
        };
    }

    struct GraphicsManager::impl{
        GLFWwindow* window;
        int window_width;
        int window_height;
        Engine* e = nullptr;

        sg_pass_action pass_action{};
    };

    void GraphicsManager::Init(Engine* e, int win_w, int win_h){
        
        /* Initialize Class members.
         */
        priv->window_width = win_w;
        priv->window_height = win_h;
        priv->e = e;

        /* Set up GLFW and open a window.
         */
        glfwInit();
        // We'll use sokol_gfx's OpenGL backend
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        priv->window = glfwCreateWindow( priv->window_width, priv->window_height, "Bingus Engine", /*fullscreen?*/false ? glfwGetPrimaryMonitor() : 0, 0 );
        glfwSetWindowAspectRatio( priv->window, priv->window_width, priv->window_height );
        if( !priv->window )
        {
            std::cerr << "Failed to create a window." << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent( priv->window );
        glfwSwapInterval(1);

        /* Set up Sokol and define a shader program.
         */
        sg_setup(sg_desc{});
        sg_buffer_desc buffer_desc{};
        buffer_desc.data = SG_RANGE(vertices);
        sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);

        sg_pipeline_desc pipeline_desc{};
        pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
        pipeline_desc.colors[0].blend.enabled = true;
        pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
        pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
        pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
        pipeline_desc.depth.write_enabled = true;
        pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
        pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

        sg_shader_desc shader_desc{};
        shader_desc.vs.source = R"(
            #version 330
            uniform mat4 projection;
            uniform mat4 transform;
            layout(location=0) in vec2 position;
            layout(location=1) in vec2 texcoords0;
            out vec2 texcoords;
            void main() {
                gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
                texcoords = texcoords0;
            })";

        shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
        // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
        shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
        shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
        shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
        shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

        shader_desc.fs.source = R"(
            #version 330
            uniform sampler2D tex;
            in vec2 texcoords;
            out vec4 frag_color;
            void main() {
                frag_color = texture( tex, texcoords );
                // If we're not drawing back to front, discard very transparent pixels so we
                // don't write to the depth buffer and prevent farther sprites from drawing.
                if( frag_color.a < 0.1 ) discard;
            })";

        shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
        shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

        pipeline_desc.shader = sg_make_shader( shader_desc );
        sg_pipeline pipeline = sg_make_pipeline( pipeline_desc );

        priv->pass_action.colors[0].action = SG_ACTION_CLEAR;
        priv->pass_action.colors[0].value = { /* red, green, blue, alpha floating point values for a color to fill the frame buffer with */ };

        sg_bindings bindings{};
        bindings.vertex_buffers[0] = vertex_buffer;
    }

    void GraphicsManager::Shutdown(){
        glfwTerminate();
        sg_shutdown();
    }

    void GraphicsManager::Draw(){
        // wawawawawawawawa (not yet implemented...)

    }

    bool GraphicsManager::ShouldQuit(){
        return glfwWindowShouldClose(priv->window);
    }

    // has to return a void* for now. Gross.
    void* GraphicsManager::window(){
        return priv->window;
    }

    GraphicsManager::GraphicsManager() : priv(std::make_unique<impl>()){}
    GraphicsManager::~GraphicsManager() = default;
}