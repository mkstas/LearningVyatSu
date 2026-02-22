namespace labaratory_work_2.Models
{
    abstract public class Dish(string name, int weight, double price)
    {
        public string Name { get; } = name;
        public int Weight { get; } = weight;
        public double Price { get; } = price;

        public virtual void DisplayInfo()
        {
            Console.WriteLine($"Dish: {Name}, {Weight}g, ${Price:F2}");
        }

        public virtual double GetFullPrice()
        {
            return Price * 1.2;
        }
    }
}
