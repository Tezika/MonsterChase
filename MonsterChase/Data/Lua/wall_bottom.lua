gameObject = 
{
    name = "Wall_Bottom",
    initial_position = {x=0,y=-295},
    initial_velocity = {x=0,y=0},
    physics_settings = {
        mass = 200,
        force = {x=0, y=0},
        dragness = 0,
        AABB = 
        {
            center = {x=0, y=1},
            extends = {x=500, y=1}
        },
        collidable = true,
        reflectable = false
    },
    render_settings = {
        sprite_name = "Data\\wall.dds",
        sprite_size = {x=256, y=256}
    }
}