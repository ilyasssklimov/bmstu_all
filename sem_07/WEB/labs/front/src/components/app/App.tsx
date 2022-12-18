import Header from "../header/Header"
import Footer from "../footer/Footer"
import Post from "../post/Post"


const App = () => {
    return (
        <div className="app">
            <Header/>
            <Post name="Название поста" author="login" city="Москва" date="15.10.2022"
            information="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vehicula, eros eleifend pretium condimentum, felis arcu sodales leo, at hendrerit tellus odio in massa. Aenean augue lacus, maximus ut tempor vitae, congue vel nibh. Vivamus eu pretium massa, at fringilla leo. Aliquam erat volutpat. In sit amet nisl ac risus pharetra convallis vel vel leo." 
            />
            <Footer/>
        </div>
    )
}

export default App;